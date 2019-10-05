#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>

# define BUFF_SIZE 4096

pid_t	g_child_pid;
char	**g_env;

char	*get_user_command(void);
void	input_clean(char **split_buff, char *buff);
void	minishell();
void	env_clean();

void	builtin_cd(char **buff);
void	builtin_exit(char **buff);
void	builtin_echo(char **buff);
void	builtin_env();
void	builtin_setenv(char **buff);
void	builtin_unsetenv(char **buff);

int		get_val(char **buff);
char	*get_homedir(char *path);
void	rel_to_home(char **buff);

void	execute(char **buff); /* TODO: change logic */
void	handle_sigint(int sig);

#endif
