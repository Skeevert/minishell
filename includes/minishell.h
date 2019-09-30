#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/types.h>

# define BUFF_SIZE 4096

char	*get_user_command(void);
void	parse_input(char **buff, char ***env);
void	env_clean(char **env);

void	builtin_cd(char **buff, char **env);
void	builtin_exit(char **buff, char ***env);
void	builtin_echo(char **buff);
void	builtin_env(char **envp);
void	builtin_setenv(char ***env, char **buff);
void	builtin_unsetenv(char **env, char **buff);

char	*get_homedir(char **env, char *path);
void	rel_to_home(char **env, char **buff);

#endif
