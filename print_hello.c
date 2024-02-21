#include <unistd.h>

/**
 * print_hello - prints "Hello, Betty!" using write function
*/
void print_hello(void)
{
	char *str = "Hello, Betty!\n";
	write(1, str, 13);
}
