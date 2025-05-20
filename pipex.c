#include "pipex.h"

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

char	*get_next_path(char *path)
{
	int			i;
	static char	*res;

	i = 0;
	while (path[i])
	{
		i++;
	}
}

int	check_call(char **argv, char **envp)
{
	char	*path;
	
	path = get_path(envp);
	while (*path && !access())
}

char	**get_argv(char **argv, char **envp)
{
	char	**res;
	
	res = (char **)malloc(sizeof(char *) * 3);
	if (!res)
		return(NULL);
	res[0] = ft_strjoin(ft_strjoin(get_path(envp), "/"), argv[1]);
	res[0] = "/usr/bin/cat";
	printf("%s\n", res[0]);
	res[1] = "/home/dgrigor2/Desktop/pipex/pipex.c";
	res[2] = NULL;
	return (res);

}

int	main(int argc, char **argv, char **envp)
{
	int	p;
	int	fd;

	(void)argc;
	//printf("%s%i\n", get_path(envp), argc);
	p = fork();
	if (p == 0) //child
	{

		fd = open(argv[2], O_RDWR);
		if (fd < 0)
			return (0);
		//printf("fkjsdhfjksdf\n\n\n");
		//execve(ft_strjoin(ft_strjoin(get_path(envp), "/"), argv[1]), get_argv(argv, envp), envp);
		execve("/usr/bin/cat", get_argv(argv, envp), envp);
	}

}