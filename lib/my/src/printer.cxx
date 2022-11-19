#include "printer.hxx"

#include <cstdarg>
#include <cstdio>
#include <memory>

namespace my {

static std::unique_ptr<Printer> GlobalPrinter;

void _set_printer_internal(Printer&& p)
{
	GlobalPrinter = std::make_unique<Printer>(std::forward<Printer>(p));
}

bool print(char const* format, ...)
{
	bool ok = false;

	if (GlobalPrinter) {
		va_list args {};
		va_start(args, format);

		const auto buffer_len = vsnprintf(nullptr, 0, format, args) + 1;
		auto buffer = new char[buffer_len] {};
		std::vsnprintf(buffer, buffer_len, format, args);

		va_end(args);
		GlobalPrinter->print(buffer);
		delete[] buffer;
		ok = true;
	}

	return ok;
}

}  // namespace my
