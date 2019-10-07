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
		env_clean();
		exit(ft_atoi(buff[1]));
	}
	else
	{
		env_clean();
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

void	change_dir(char *path)
{
	char	pwd[PATH_MAX];
	int 	i;

	i = 0;
	while (ft_strncmp(g_env[i], "OLDPWD=", 7))
		i++;
	getcwd(pwd, PATH_MAX);
	if (chdir(path))
	{
		write(2, "Not a Directory\n", 16);
		return ;
	}
	free(g_env[i]);
	if (!(g_env[i] = ft_strjoin("OLDPWD=", pwd)))
		return ;
	getcwd(pwd, PATH_MAX);
	i = 0;
	while (ft_strncmp(g_env[i], "PWD=", 4))
		i++;
	free(g_env[i]);
	if (!(g_env[i] = ft_strjoin("PWD=", pwd)))
		return ;
}

void	builtin_cd(char **buff)
{
	char	path[PATH_MAX + 1];
	int		i;

	if (!buff[1])
		change_dir(get_homedir(path));
	else if (buff[2])
		write(2, "not in pwd\n", 11); /* TODO: change */
	else if (buff[1][0] == '~')
		rel_to_home(buff);
	else if (buff[1][0] == '-' && !buff[1][1])
	{
		i = 0;
		while (ft_strncmp(g_env[i], "OLDPWD=", 7))
			i++;
		change_dir(g_env[i] + 7);
	}
	else if (access(buff[1], F_OK))
		write(2, "cannot find\n", 12); /* TODO: change */
	else
		change_dir(buff[1]);
}
