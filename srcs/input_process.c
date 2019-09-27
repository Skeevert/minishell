#include "minishell.h"

void	parse_input(char **buff, char **envp)
{
	if (!buff || !buff[0])
		return ;
	if (!(ft_strcmp(buff[0], "cd")))
		builtin_cd(buff, envp);
	else if (!(ft_strcmp(buff[0], "echo")))
		builtin_echo(buff);
	else if (!(ft_strcmp(buff[0], "setenv")))
		ft_putstr("setenv invoked\n");
	else if (!(ft_strcmp(buff[0], "unsetenv")))
		ft_putstr("unsetenv invoked\n");
	else if (!(ft_strcmp(buff[0], "env")))
		builtin_env(envp);
	else if (!(ft_strcmp(buff[0], "exit")))
		builtin_exit(buff);
	else
		ft_putstr("Not a builtin\n");
}
