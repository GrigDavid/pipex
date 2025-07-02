/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_to_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgrigor2 <dgrigor2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:23:06 by dgrigor2          #+#    #+#             */
/*   Updated: 2025/07/02 16:28:40 by dgrigor2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static void	ft_free_mat(char **arr)
{
	int	j;

	j = 0;
	while (arr[j])
	{
		free(arr[j]);
		j++;
	}
	free(arr);
}

static char	*ft_strjoin_chr(char *str, char c, char *dst)
{
	int		i;
	int		len;
	char	*res;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			break ;
		i++;
	}
	len = ft_strlen(dst);
	res = (char *)malloc((i + len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	res[i-- + len] = 0;
	while (i >= 0)
	{
		res[i + len] = str[i];
		i--;
	}
	while (len-- > 0)
		res[len] = dst[len];
	return (res);
}

static char	*check_prog(char **paths, char *file)
{
	char	*tmp;
	int		i;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin_chr(file, ' ', paths[i++]);
		if (!tmp)
			return (free(file), ft_free_mat(paths), NULL);
		if (!access(tmp, F_OK) && !access(tmp, X_OK))
			return (free(file), ft_free_mat(paths), tmp);
		free(tmp);
	}
	return (free(file), ft_free_mat(paths), NULL);
}

char	*set_to_path(char **envp, char *file)
{
	char	*tmp;
	char	**paths;

	if (!file)
		return (NULL);
	if (*file == '.' || *file == '/')
	{
		if (!access(file, F_OK) && !access(file, X_OK))
			return (file);
		return (NULL);
	}
	tmp = get_path(envp);
	if (!tmp)
		return (NULL);
	paths = ft_split(tmp, ':');
	if (!paths)
		return (NULL);
	file = ft_strjoin("/", file);
	if (!file)
		return (ft_free_mat(paths), NULL);
	return (check_prog(paths, file));
}
