#include "../pipex.h"

char	*read_file(char *file)
{
	char	*res;
	char	*tmp;
	int		fd;

	res = NULL;
	
	fd = open (file, O_RDONLY);
	if (fd == -1)
		return(NULL);
	tmp = ft_calloc(sizeof(char), 101);
	if (!tmp)
		return(NULL);
	tmp = get_next_line(fd);
	while (tmp)
	{
		//printf("%s\n", tmp);
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
	//printf("hey %s\n", res);
	return (res);
}