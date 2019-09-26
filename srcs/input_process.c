#include "minishell.h"

void	parse_input(char **buff)
{
	if (!buff || !buff[0])
		return ;
	if (!(ft_strcmp(buff[0], "cd")))
		ft_putstr("cd invoked\n");
	else if (!(ft_strcmp(buff[0], "echo")))
		ft_putstr("echo invoked\n");
	else if (!(ft_strcmp(buff[0], "setenv")))
		ft_putstr("setenv invoked\n");
	else if (!(ft_strcmp(buff[0], "unsetenv")))
		ft_putstr("unsetenv invoked\n");
	else if (!(ft_strcmp(buff[0], "env")))
		ft_putstr("env invoked\n");
	else if (!(ft_strcmp(buff[0], "exit")))
		builtin_exit(buff);
	else
		ft_putstr("Not a builtin\n");
}
