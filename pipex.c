#include "pipex.h"





void	x_cmd(int *fd, char **argv, char **envp)
{
	int	pid;
	char	**arg;

	arg = (char **)malloc(sizeof(char *) * 2);
	if (!arg)
		return ;
	arg[0] = argv[2];
	arg[1] = NULL;
	pid = fork();
	if (pid == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		//printf("%s\n", set_to_path(envp, argv[2]));
		execve(set_to_path(envp, argv[2]), arg, envp);
	}
	wait(NULL);
}


int	main(int argc, char **argv, char **envp)
{
	int	fds[2];
	char	*content;

	content = read_file(argv[1]);

	if (pipe(fds) == -1)
		return (1);
	argc+=0;
	write(fds[1], content, ft_strlen(content));
	close(fds[1]);
	x_cmd(fds, argv, envp);
	return(0);
}