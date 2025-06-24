# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>

int	main(void)
{
	char	*arr;
	int		len;

	arr = NULL;
	arr = (char *)calloc(100, 1);
	if (!arr)
		return (1);
	if (read(0, arr, 100) == -1)
		return (1);
	write(1, arr, 100);
	free(arr);
	return (0);
}