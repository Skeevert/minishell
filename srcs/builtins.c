#include "minishell.h"

void	builtin_exit(char **buff, char ***env)
{
	if (buff[1])
	{
		if (buff[2])
		{
			write(2, "exit: too many arguments\n", 25);
			return ;
		}
		env_clean(*env);
		exit(ft_atoi(buff[1]));
	}
	else
	{
		env_clean(*env);
		exit(0); /* TODO: if specified, exit with the return of previous program */
	}
}

void	builtin_echo(char **buff)
{
	int		i;

	i = 1;
	while (buff[i])
	{
		ft_putstr(buff[i]);
		buff[i + 1] ? write(1, " " , 1) : 0;
		i++;
	}
	write(1, "\n", 1);
}

void	builtin_cd(char **buff, char **env)
{
	char	path[PATH_MAX + 1];

	if (!buff[1])
		chdir(get_homedir(env, path));
	else if (buff[1][0] == '~')
		rel_to_home(env, buff);
	else if (buff[2])
		write(2, "not in pwd\n", 11); /* TODO: change */
	else if (access(buff[1], F_OK))
		write(2, "cannot find\n", 12); /* TODO: change */
	else
		if (chdir(buff[1]))
			write(2, "is not a directory\n", 19);
}
