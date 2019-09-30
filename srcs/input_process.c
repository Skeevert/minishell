#include "minishell.h"

void	parse_input(char **buff, char ***env)
{
	if (!buff || !buff[0])
		return ;
	if (!(ft_strcmp(buff[0], "cd")))
		builtin_cd(buff, *env);
	else if (!(ft_strcmp(buff[0], "echo")))
		builtin_echo(buff);
	else if (!(ft_strcmp(buff[0], "setenv")))
		builtin_setenv(env, buff);
	else if (!(ft_strcmp(buff[0], "unsetenv")))
		builtin_unsetenv(*env, buff);
	else if (!(ft_strcmp(buff[0], "env")))
		builtin_env(*env);
	else if (!(ft_strcmp(buff[0], "exit")))
		builtin_exit(buff, env);
	else
		ft_putstr("Not a builtin\n");
}
