#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int	id;
	int	fd[2];
	//int	input;
	char	*tmp;
	argc += 0;
	argv += 0;
	envp += 0;
	tmp = (char *)malloc(100);
	if (!tmp)
		return (1);
	if (pipe(fd) == -1)
		return (1);
	id = fork();
	//printf("\n%s\n\n", get_path(envp));
	if (id == 0)//child
	{
		close(fd[0]);
		//write(1, "\ninput: ", 8);
		while (read(0, tmp, 100) == 0)
		{}
		if (!tmp)
			return (1);
		write(fd[1], tmp, ft_strlen(tmp));
		close(fd[1]);
	}
	else
	{
		wait(NULL);
		close(fd[1]);
		//write(1, "\noutput: ", 9);
		read (fd[0], tmp, 100);
		//printf("%s\n", tmp);
		int	filefd = open("file1", O_WRONLY);
		dup2(filefd, 1);
		//write(1, "begemot", 12);
		//char *newargv[] = { "./echo", tmp };
		char **newargv = ft_split(ft_strjoin("./echo ", tmp), ' ');
		execve("/usr/bin/echo", newargv, envp);
		close(fd[0]);
	}
}//usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin
