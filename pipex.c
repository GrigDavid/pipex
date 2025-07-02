/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgrigor2 <dgrigor2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:22:07 by dgrigor2          #+#    #+#             */
/*   Updated: 2025/07/02 16:32:58 by dgrigor2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_shell(char **envp)
{
	char	*path;

	if (!*envp)
		return (NULL);
	while (*envp)
	{
		if (ft_strncmp(*envp, "SHELL=", 5))
			envp++;
		else
		{
			path = *envp + 5;
			break ;
		}
	}
	if (!*envp)
		return (NULL);
	path = ft_strrchr(path, '/') + 1;
	return (path);
}

void	send_error(char **envp)
{
	if (!*envp)
		ft_putstr_fd("environment not loaded\n", 2);
	else if (errno)
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
	close(fd_in);
	close(fd_out);
	path = set_to_path(envp, name);
	if (!path)
		return (send_error(envp), 0);
	execve(path, arg, envp);
	return (send_error(envp), 0);
}

int	kanchox_zibil(char **argv, char **envp)
{
	int	pid1;
	int	pid2;
	int	file_fd;
	int	p[2];
	int	status;

	if (pipe(p) < 0)
		return (send_error(envp), errno);
	pid1 = fork();
	if (pid1 < 0)
		return (send_error(envp), errno);
	if (pid1 == 0)
	{
		close(p[0]);
		file_fd = open(argv[1], O_RDONLY);
		if (file_fd < 0)
			return (close(p[1]), send_error(envp), errno);
		x_cmd(file_fd, p[1], argv[2], envp);
		return (errno);
	}
	pid2 = fork();
	if (pid2 < 0)
		return (send_error(envp), errno);
	if (pid2 == 0)
	{
		close(p[1]);
		file_fd = open(argv[4], O_TRUNC | O_WRONLY | O_CREAT, 0644);
		if (file_fd < 0)
			return (close(p[0]), send_error(envp), errno);
		x_cmd(p[0], file_fd, argv[3], envp);
		return (errno);
	}
	close(p[0]);
	close(p[1]);
	wait(&status);
	if (WIFEXITED(status))
		if (WEXITSTATUS(status))
			return (errno);
	wait(&status);
	if (WIFEXITED(status))
		if (WEXITSTATUS(status))
			return (errno);
	return (errno);
}

int	main(int argc, char **argv, char **envp)
{
	char	*tmp;
	
	if (argc != 5)
		return (1);
	if (!get_shell(envp))
	{
		send_error(envp);
		return (1);
	}
	tmp = set_to_path(envp, argv[2]);
	if (!tmp)
	{
		send_error(envp);
		return (1);
	}
	free(tmp);
	tmp = set_to_path(envp, argv[3]);
	if (!tmp)
	{
		send_error(envp);
		return (1);
	}
	free(tmp);
	return (kanchox_zibil(argv, envp));
}

/*
	*** POSSIBLE ISSUES ***

	- file2 contains something
	- file2 doesn't exist
	- child proccess results in an error

*/
