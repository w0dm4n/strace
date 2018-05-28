#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

int main()
{
	write(1, "bonjourallelujah\n", 18);
	malloc(666);
	write(1, "bonjour\n", 8);
	
	int res = open("salope", O_RDWR);
	printf("%d\n", res);
	return 0;
}
