#include "pipex.h"

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
	//printf("huys uneir kashxater? %s\n", tmp);
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

int	validate(int argc, char ** argv)
{
	if (argc != 5)//check argc
		return (0);
	if (access(argv[1], F_OK))//check file1 existence
		{if (!access(argv[1], R_OK))//check file1 readability
			return (0);}
	else
		return (0);
	if (access(argv[4], F_OK))
		{if (!access(argv[4], W_OK))
			return (0);}
	else
		return (0);
	return (1);
}

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

int	main(int argc, char **argv, char **envp)//////////////////////////////////////////////////this is still work in progress, almost nothing works:)
{
	char	*file1;
	int		fd1;
	int		fd2;
	//int		stdout;
	char	**arg;

	arg = (char **)malloc(sizeof(char *) * 2);
	if (!arg)
		return (1);
	argc+=0;
	envp+=0;
	// if (!validate(argc, argv))
	// 	return (1);
	//printf("ku\n");
	file1 = read_file(argv[1]);
	printf("%s\n", file1);
	if (!file1)
		return(1);
	//stdout = dup(1);
	arg[0] = argv[2];
	arg[1] =  file1;
	//printf("%s\n", set_to_path(envp, argv[2]));
	fd1 = dup(0);
	dup2(fd2, 0);
	execve(set_to_path(envp, argv[2]), arg, envp);

}