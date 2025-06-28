#include "pipex.h"

void	x_cmd(int fd_in, int fd_out, char *name, char **envp)
{
	char	**arg;
	char	*path;

	arg = (char **)malloc(sizeof(char *) * 2);
	if (!arg)
		return ;
	arg = ft_split(name, ' ');
	if (!arg)
		return ;
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_in);
	close(fd_out);
	path = set_to_path(envp, name);
	if (!path)
		return ;	
	execve(path, arg, envp);
}

void	kanchox_zibil(char **argv, char **envp)
{
	int	pid;
	int	file1_fd;
	int	file2_fd;
	int	p[2];

	if (pipe(p) == -1)
		return ;
	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
	{
		file1_fd = open(argv[1], O_RDONLY);
		if (file1_fd < 0)
			return ;
		close(p[0]);
		x_cmd(file1_fd, p[1], argv[2], envp);
	}
	waitpid(pid, NULL, 0);
	close(p[1]);
	file2_fd = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0777); // turn this into if statement so if the file does not exist than on error it should be deleted using unlink()
	if (file2_fd == -1)
		return ;
	x_cmd(p[0], file2_fd, argv[3], envp);
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
