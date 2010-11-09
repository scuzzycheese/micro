#include "404.h"

int error404(struct argData *args)
{
	fib_send("<html><head><title>404 Not Found</title></head>");
	fib_send("<body><h1>Error: 404</h1>");
	fib_send("<b>Page not found!<br/></body></html>");
}
