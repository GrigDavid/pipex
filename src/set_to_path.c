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
	int	i;
	int	len;
	char	*res;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			break;
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

static int	check_prog(char *file)
{
	if (!access(file, F_OK) && !access(file, X_OK))
		return (1);
	return (0);
}

char	*set_to_path(char **envp, char *file)
{
	char	*tmp;
	char	**paths;
	int		i;

	i = 0;
	if (*file == '.' || *file == '/')
	{
		if (check_prog(file))
			return (file);
		return (NULL);
	}
	tmp = get_path(envp);
	if (!tmp)
		return(NULL);
	paths = ft_split(tmp, ':');
	if (!paths)
		return (NULL);
	file = ft_strjoin("/", file);
	if (!file)
		return(ft_free_mat(paths), NULL);
	while (paths[i])
	{
		tmp = ft_strjoin_chr(file, ' ', paths[i++]);
		if (!tmp)
			return (free(file), ft_free_mat(paths), NULL);
		if (check_prog(tmp))
			return (free(file),ft_free_mat(paths), tmp);
		free(tmp);
	}
	return(free(file), ft_free_mat(paths), NULL);
}

