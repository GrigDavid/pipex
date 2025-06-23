#include "pipex.h"

void	x_cmd(int fd_in, int fd_out, char *name, char **envp)
{
	char	**arg;

	arg = (char **)malloc(sizeof(char *) * 2);
	if (!arg)
		return ;
	arg[0] = name;
	arg[1] = NULL;
	//pid = fork();
	//printf("%d\n", pid);

	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_in);
	// printf("%s\n", set_to_path(envp, name));
	execve(set_to_path(envp, name), arg, envp);	
	close(fd_out);
	wait(NULL);
}

void	kanchox_zibil(int *pipe1, int *pipe2, char **argv, char **envp)
{
	int	fd;
	int	pid_c1;
	int	pid_c2;

	pid_c1 = fork();
	wait(NULL);
	if (pid_c1 == 0)
	{
		pid_c2 = fork();
		if (pid_c2 == 0)
		{
			x_cmd(pipe1[0], pipe2[1], argv[2], envp);
		}
		fd = open (argv[4], O_WRONLY);
		if (fd == -1)
			return ;
		pipe1[1] = open(pipe1[1], O_WRONLY);
		x_cmd(pipe2[0], pipe1[1], argv[3], envp);
		char	*str = read_fd(pipe1[0]);
		write(fd, str, ft_strlen(str));
	}
	
	//x_cmd(pipe2[0], fd, argv[3], envp);
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
	kanchox_zibil(pipe1, pipe2, argv, envp);
	
	
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
