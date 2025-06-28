#include "pipex.h"

char	*get_shell(char **envp)
{
	char	*path;

	while (*envp)
	{
		if (ft_strncmp(*envp, "SHELL=", 5))
			envp++;
		else
		{
			path = *envp + 5;
			break;
		}
	}
	if (!*envp)
		return (NULL);
	path = ft_strrchr(path, '/') + 1; 
	return(path);
}

void	send_error(char **envp)
{
	if (errno)
	{
		perror(get_shell(envp));
	}
	else
	{
		ft_putstr_fd(get_shell(envp), 2);
		ft_putstr_fd("an unexpected error occured\n", 2);
	}
}


int	x_cmd(int fd_in, int fd_out, char *name, char **envp)
{
	char	**arg;
	char	*path;

	arg = (char **)malloc(sizeof(char *) * 2);
	if (!arg)
		return (send_error(envp), 0);
	arg = ft_split(name, ' ');
	if (!arg)
		return (send_error(envp), 0);
	if (dup2(fd_in, STDIN_FILENO) < 0)
		return (send_error(envp), 0);
	if (dup2(fd_out, STDOUT_FILENO) < 0)
		return (send_error(envp), 0);
	if (close(fd_in) < 0)
		return (send_error(envp), 0);
	if (close(fd_out) < 0)
		return (send_error(envp), 0);
	path = set_to_path(envp, name);
	if (!path)
		return (send_error(envp), 0);	
	execve(path, arg, envp) < 0
	return (send_error(envp), 0);
}

int	kanchox_zibil(char **argv, char **envp)
{
	int	pid;
	int	file1_fd;
	int	file2_fd;
	int	p[2];

	if (pipe(p) < 0)
		return (send_error(envp), 0);
	pid = fork();
	if (pid < 0)
		return (send_error(envp), 0);
	if (pid == 0)
	{
		if (close(p[0]) < 0)
			return (send_error(envp), 0);
		file1_fd = open(argv[1], O_RDONLY);
		if (file1_fd < 0)//pipes stay open aziz jan
			return (send_error(envp), 0);
		x_cmd(file1_fd, p[1], argv[2], envp);
		return (0);
	}
	if (close(p[1]) < 0)
		return (send_error(envp), 0);
	file2_fd = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (file2_fd < 0)
		return (send_error(envp), 0);
	x_cmd(p[0], file2_fd, argv[3], envp);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc != 5)
		return (1);
	kanchox_zibil(argv, envp);
	return (0);
}

/*
	*** POSSIBLE ISSUES ***

	- file2 contains something
	- file2 doesn't exist
	- child proccess results in an error

*/
