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

char	*set_to_path(char **envp, char *file)
{
	char	*tmp;
	char	**paths;
	int		i;

	i = 0;
	if (*file == '.' || *file == '/')
		return (file);
	paths = ft_split(get_path(envp), ':');
	if (!paths)
		return (NULL);
	file = ft_strjoin("/", file);
	if (!file)
		return(NULL);
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i++], file);
		if (!tmp)
		{
			ft_free_mat(paths);
			return (NULL);
		}
		if (!access(tmp, F_OK) && !access(tmp, X_OK))
		{
			ft_free_mat(paths);
			return (tmp);
		}
		free(tmp);
	}
	ft_free_mat(paths);
	return(NULL);
}
