#include "minishell.h"

void	builtin_exit(char **buff)
{
	if (buff[1])
	{
		if (buff[2])
		{
			write(2, "exit: too many arguments\n", 25);
			return ;
		}
		exit(ft_atoi(buff[1]));
	}
	else
		exit(0); /* TODO: if specified, exit with the return of previous program */
}
