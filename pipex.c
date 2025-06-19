#include "pipex.h"

void	x_cmd(int *pipe1, int *pipe2, char **argv, char **envp)
{
	int		pid;
	char	**arg;

	pipe2+=0;
	arg = (char **)malloc(sizeof(char *) * 2);
	if (!arg)
		return ;
	arg[0] = argv[2];
	arg[1] = NULL;
	pid = fork();
	if (pid == 0)
	{
		dup2(pipe1[0], STDIN_FILENO);
		dup2(pipe2[1], STDOUT_FILENO);
		close(pipe1[0]);
		//printf("%s\n", set_to_path(envp, argv[2]));
		execve(set_to_path(envp, argv[2]), arg, envp);
	}
	close(pipe1[0]);
	wait(NULL);
}

int	main(int argc, char **argv, char **envp)
{
	int	pipe1[2];
	int	pipe2[2];
	char	*content;

	content = read_file(argv[1]);//you need 2nd pipe, use a structure like in the bottom of file
	if (!content)
		return (1);
	if (pipe(pipe1) == -1)
		return (1);
	if (pipe(pipe2) == -1)
		return (-1);
	argc += 0;
	write(pipe1[1], content, ft_strlen(content));
	close(pipe1[1]);
	x_cmd(pipe1, pipe2, argv, envp);
	return (0);
}

/*

   [parent]
   /     \
  /       \
[p]        [c1]
           /  \
		  /    \
		 [c1]  [c2]
		  |     |
		[cmd2] [cmd1]



*/
