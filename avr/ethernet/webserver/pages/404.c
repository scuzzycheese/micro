#include "404.h"

int error404(struct argData *args, coStData *regs)
{
	fib_send("<h1>Error: 404</h1>", regs);
	fib_send("<b>Page not found!<br/>", regs);
}
