#include <stdio.h>

#define MYDEBUG(fmt, ...) { printf("[%s:%d] %s "fmt, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__); }

int main()
{
	printf("hello world\n");

	MYDEBUG("hello world\n");
}