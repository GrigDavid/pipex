#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "libft.h"
# include <fcntl.h>
# include <sys/wait.h>

char	*get_path(char **envp);

#endif