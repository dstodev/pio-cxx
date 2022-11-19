#include "printer.hxx"

#include <memory>

namespace my {

static std::unique_ptr<Printer> GlobalPrinter;

void _set_printer_internal(Printer&& p)
{
	GlobalPrinter = std::make_unique<Printer>(std::forward<Printer>(p));
}

void print(char const* message)
{
	if (GlobalPrinter) {
		GlobalPrinter->print(message);
	}
}

}  // namespace my
