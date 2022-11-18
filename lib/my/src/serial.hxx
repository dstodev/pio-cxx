#ifndef PIO_CXX_SERIAL_HXX
#define PIO_CXX_SERIAL_HXX

#include <memory>

class Serial
{
	struct ISerial
	{
		virtual ~ISerial() = 0;
		virtual void print(char const* message) const = 0;
	};

	template <typename T>
	struct SerialModel : ISerial
	{
		T object;
		explicit SerialModel(T state)
		    : object {state}
		{}
		void print(char const* message) const override
		{
			// Expects T::print(char const*)
			object.print(message);
		}
	};
	std::unique_ptr<ISerial> _impl;

public:
	template <typename T>
	explicit Serial(T serial)
	    : _impl {new SerialModel<T>(serial)}
	{}

	void print(char const* message) const
	{
		_impl->print(message);
	}

	Serial(Serial&& move) = default;
	Serial& operator=(Serial&& move) = default;
};

inline Serial::ISerial::~ISerial() = default;

#endif  // PIO_CXX_SERIAL_HXX
