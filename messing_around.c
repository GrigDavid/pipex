#include <unistd.h>
#include <stdio.h>

// int	main(int argc, char **argv)
// {
// 	int	pid;

// 	pid = fork();

// 	if (pid == -1)
// 	{
// 		printf("nigga what?");
// 		return (0);
// 	}
// 	if (pid == 0)
// 		printf("I'm child process\n");
// 	else
// 		{
// 			wait(NULL);
// 			printf ("I'm  parent process\n");
// 		}
// 	return(0);
// }


int	main(int argc, char **argv, char *envp[])
{
	int	i;

	i = 0;
	while (*envp)
		printf("%s\n", *(envp++));
	
}
