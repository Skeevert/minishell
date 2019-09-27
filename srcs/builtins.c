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

void	builtin_cd(char **buff)
{
	if (!buff[1])
	{
		chdir("~");
		return ;
	}
	else if (buff[2])
	{
		write(2, "not in pwd\n", 11); /* TODO: change */
		return ;
	}
	else if (access(buff[1], F_OK))
	{
		write(2, "cannot find\n", 12); /* TODO: change */
		return ;
	}
	else
		if (chdir(buff[1]))
			write(2, "is not a directory\n", 19);
}
