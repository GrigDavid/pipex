/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgrigor2 <dgrigor2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:23:21 by dgrigor2          #+#    #+#             */
/*   Updated: 2025/06/30 16:23:22 by dgrigor2         ###   ########.fr       */
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

#endif