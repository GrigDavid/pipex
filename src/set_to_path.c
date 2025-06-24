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
		tmp = ft_strjoin(paths[i++], file);
		if (!tmp)
			return (free(file), ft_free_mat(paths), NULL);
		if (check_prog(tmp))
			return (free(file),ft_free_mat(paths), tmp);
		free(tmp);
	}
	return(free(file), ft_free_mat(paths), NULL);
}

