#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/types.h>

# define BUFF_SIZE 4096

char	*get_user_command(void);
void	parse_input(char **buff, char **envp);

void	builtin_cd(char **buff, char **envp);
void	builtin_exit(char **buff);
void	builtin_echo(char **buff);
void	builtin_env(char **envp);

char	*get_homedir(char **envp, char *path);
void	rel_to_home(char **envp, char **buff);

#endif
