#include "../pipex.h"

char	*read_fd(int fd)
{
	char	*res;
	char	*tmp;
	
	res = NULL;
	tmp = ft_calloc(sizeof(char), 101);
	if (!tmp)
		return(NULL);
	tmp = get_next_line(fd);
	while (tmp)
	{
		if (!res)
			res = tmp;//malloc protection=(
		else
		{
			res = ft_strjoin(res, tmp);
			if (!res)
			{
				free(tmp);
				return(NULL);
			}
			free(tmp);
		}
		tmp = get_next_line(fd);
	}
	return(res);
}

char	*read_file(char *file)
{

	int		fd;

	
	
	fd = open (file, O_RDONLY);
	if (fd == -1)
		return(NULL);
	return (read_fd(fd));
}
