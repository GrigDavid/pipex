#include "pipex.h"

int	main(void)
{
	int	id;
	int	fd[2];
	//int	input;
	char	*tmp;

	tmp = (char *)malloc(100);
	if (!tmp)
		return (1);
	if (pipe(fd) == -1)
		return (1);
	id = fork();
	if (id == 0)
	{
		close(fd[0]);
		write(1, "\ninput a number: ", 17);
		while (read(0, tmp, 100) == 0)
		{}
		if (!tmp)
			return (1);
		write(fd[1], tmp, sizeof(int));
		close(fd[1]);
	}
	else
	{
		wait(NULL);
		close(fd[1]);
		write(1, "\ngot from your input: ", 22);
		read (fd[0], tmp, sizeof(int));
		printf("%s\n", tmp);
		close(fd[0]);
	}
}
