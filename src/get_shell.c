/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgrigor2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:56:13 by dgrigor2          #+#    #+#             */
/*   Updated: 2025/07/04 12:56:14 by dgrigor2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

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
