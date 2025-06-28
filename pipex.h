#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "libft.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>

char	*get_path(char **envp);
char	*set_to_path(char **envp, char *file);

#endif