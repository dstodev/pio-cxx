#ifndef PIO_CXX_PRINTER_HXX
#define PIO_CXX_PRINTER_HXX

#include <memory>
#include <utility>

namespace my {

class Printer
{
	struct Abstraction
	{
		virtual ~Abstraction() = 0;
		virtual void print(char const* message) /*const*/ = 0;  // not const as Arduino Serial family is not const
	};

	template <typename T>
	struct Implementation : Abstraction
	{
		T object;
		explicit Implementation(T state)
		    : object {state}
		{}
		~Implementation() override = default;
		void print(char const* message) override
		{
			// Expects T::print(char const*)
			object.print(message);
		}
	};

	std::unique_ptr<Abstraction> _impl;

public:
	template <typename T>
	explicit Printer(T object)
	    : _impl {new Implementation<T>(object)}
	{}

	void print(char const* message)
	{
		_impl->print(message);
	}

	Printer(Printer&& move) = default;
	Printer& operator=(Printer&& move) = default;
};

inline Printer::Abstraction::~Abstraction() = default;

void _set_printer_internal(Printer&& p);

/// Register global serial printer
/// Expects T::print(char const*)
template <typename T>
void set_printer(T printer)
{
	auto p = Printer(printer);
	_set_printer_internal(std::move(p));
}

/// Supports C-like printf format strings:
/// https://en.wikipedia.org/wiki/Printf_format_string
bool print(char const* format, ...);

}  // namespace my

#endif  // PIO_CXX_PRINTER_HXX
