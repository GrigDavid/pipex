#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	argc++;
	char	*str;

	str = (char *)malloc(100);
	read(0, str, 100);
	write(1, str, strlen(str));
	return (0);
}