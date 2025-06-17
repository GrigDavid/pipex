#include "pipex.h"

int	validate(int argc, char ** argv, char **envp)
{
	if (argc != 5)//check argc
		return (0);
	if (!access(argv[1], F_OK))//check file1 existance
		if (access(argv[1], R_OK))//check file1 readability
			return (0);
	else
			return(0);
	if (access(set_to_path(argv[2]), F_OK))

}

int	main(int argc, char **argv, char **envp)
{
	if (!validate(argc, argv, envp))
	{
		return (1);
	}

}