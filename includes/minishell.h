#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

# define BUFF_SIZE 4096

char	*get_user_command(void);
void	parse_input(char **buff);

void	builtin_exit(char **buff);

#endif
