/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgrigor2 <dgrigor2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:22:58 by dgrigor2          #+#    #+#             */
/*   Updated: 2025/06/30 16:26:28 by dgrigor2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*get_path(char **envp)
{
	char	*path;

	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5))
			envp++;
		else
		{
			path = *envp + 5;
			break ;
		}
	}
	if (!*envp)
		return (NULL);
	return (path);
}
