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
			break;
		}
	}
	if (!*envp)
		return (NULL);
	return(path);
}