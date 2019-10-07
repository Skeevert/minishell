/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshawand <hshawand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 14:50:02 by hshawand          #+#    #+#             */
/*   Updated: 2019/10/07 16:44:57 by hshawand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		exit(0);
	}
}

void	echo_print(char *str)
{
	char	out[1024];
	char	*out_p;
	int		i;

	i = 0;
	out_p = out;
	ft_bzero(out, 1024);
	while (i < 1023 && *str)
	{
		*str != '"' ? *out_p = *str : 0;
		*str != '"' ? out_p++ : 0;
		str++;
		i++;
	}
	ft_putstr(out);
	*str ? echo_print(str) : 0;
}

void	builtin_echo(char **buff)
{
	int		i;
	int		j;
	int		q_num;

	i = 1;
	q_num = 0;
	while (buff[i])
	{
		j = 0;
		while (buff[i][j])
			buff[i][j++] == '"' ? q_num++ : 0;
		i++;
	}
	if (q_num % 2)
		return (void_err(5));
	i = 1;
	while (buff[i])
	{
		echo_print(buff[i]);
		buff[i + 1] ? ft_putchar(' ') : 0;
		i++;
	}
	write(1, "\n", 1);
}

void	change_dir(char *path)
{
	char	pwd[PATH_MAX];
	int		i;

	i = 0;
	while (ft_strncmp(g_env[i], "OLDPWD=", 7))
		i++;
	getcwd(pwd, PATH_MAX);
	if (chdir(path))
		return (void_err(1));
	free(g_env[i]);
	if (!(g_env[i] = ft_strjoin("OLDPWD=", pwd)))
		return (void_err(0));
	getcwd(pwd, PATH_MAX);
	i = 0;
	while (ft_strncmp(g_env[i], "PWD=", 4))
		i++;
	free(g_env[i]);
	if (!(g_env[i] = ft_strjoin("PWD=", pwd)))
		return (void_err(0));
}

void	builtin_cd(char **buff)
{
	char	path[PATH_MAX + 1];
	int		i;

	if (!buff[1])
		change_dir(get_homedir(path));
	else if (buff[2])
		void_err(2);
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
		void_err(3);
	else
		change_dir(buff[1]);
}
