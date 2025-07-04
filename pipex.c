/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgrigor2 <dgrigor2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:54:32 by dgrigor2          #+#    #+#             */
/*   Updated: 2025/07/04 12:58:06 by dgrigor2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	x_cmd(int fd_in, int fd_out, char *name, char **envp)
{
	char	**arg;
	char	*path;

	arg = ft_split(name, ' ');
	if (!arg)
		return (ft_free_mat(arg), send_error(envp), 0);
	if (dup2(fd_in, STDIN_FILENO) < 0)
		return (ft_free_mat(arg), send_error(envp), 0);
	if (dup2(fd_out, STDOUT_FILENO) < 0)
		return (ft_free_mat(arg), send_error(envp), 0);
	close(fd_in);
	close(fd_out);
	path = set_to_path(envp, name);
	if (!path)
		return (ft_free_mat(arg), 0);
	execve(path, arg, envp);
	return (0);
}

int	validate(char *cmd, char **envp)
{
	char	*tmp;

	tmp = set_to_path(envp, cmd);
	if (!tmp)
		return (0);
	free(tmp);
	return (1);
}

int	call_second_fork(char **argv, char **envp, int pid1, int p[2])
{
	int	pid2;
	int	status;
	int	file_fd;

	pid2 = fork();
	if (pid2 < 0)
		return (send_error(envp), errno);
	if (pid2 == 0)
	{
		close(p[1]);
		file_fd = open(argv[4], O_TRUNC | O_WRONLY | O_CREAT, 0644);
		if (file_fd < 0 || !validate(argv[3], envp))
			return (close(p[0]), send_error(envp), 1);
		x_cmd(p[0], file_fd, argv[3], envp);
		return (errno);
	}
	close(p[0]);
	close(p[1]);
	waitpid(pid1, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status))
		return (0);
	wait(&status);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}

int	call_fork(char **argv, char **envp)
{
	int	pid1;
	int	file_fd;
	int	p[2];

	if (pipe(p) < 0)
		return (send_error(envp), 1);
	pid1 = fork();
	if (pid1 < 0)
		return (send_error(envp), 1);
	if (pid1 == 0)
	{
		close(p[0]);
		file_fd = open(argv[1], O_RDONLY);
		if (file_fd < 0)
			return (send_error(envp), 0);
		x_cmd(file_fd, p[1], argv[2], envp);
		return (0);
	}
	return (call_second_fork(argv, envp, pid1, p));
}

int	main(int argc, char **argv, char **envp)
{
	errno = 0;
	if (argc != 5)
		return (1);
	if (!get_shell(envp))
	{
		send_error(envp);
		return (errno);
	}
	return (call_fork(argv, envp));
}
