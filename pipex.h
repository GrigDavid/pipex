/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgrigor2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:54:13 by dgrigor2          #+#    #+#             */
/*   Updated: 2025/07/04 12:54:17 by dgrigor2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "libft.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>

char	*get_path(char **envp);
char	*set_to_path(char **envp, char *file);
void	ft_free_mat(char **arr);
char	*get_shell(char **envp);
void	send_error(char **envp);

#endif
