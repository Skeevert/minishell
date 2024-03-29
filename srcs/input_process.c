/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshawand <hshawand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 14:48:24 by hshawand          #+#    #+#             */
/*   Updated: 2019/10/07 22:29:13 by hshawand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_input(char **buff)
{
	if (get_val(buff))
		return ;
	if (!buff || !buff[0])
		return ;
	if (!(ft_strcmp(buff[0], "cd")))
		builtin_cd(buff);
	else if (!(ft_strcmp(buff[0], "echo")))
		builtin_echo(buff);
	else if (!(ft_strcmp(buff[0], "setenv")))
		builtin_setenv(buff);
	else if (!(ft_strcmp(buff[0], "unsetenv")))
		builtin_unsetenv(buff);
	else if (!(ft_strcmp(buff[0], "env")))
		builtin_env();
	else if (!(ft_strcmp(buff[0], "exit")))
		builtin_exit(buff);
	else
		execute(buff);
}

void	form_curr_path(void)
{
	char	curr_path[PATH_MAX + 3];

	getcwd(curr_path, PATH_MAX);
	ft_strcat(curr_path, "> ");
	ft_putstr("\x1b[33m");
	write(1, curr_path, strlen(curr_path));
	ft_putstr("\x1b[0m");
}

char	*get_user_command(void)
{
	char	*command;
	char	temp;
	char	save[BUFF_SIZE + 1];
	int		i;

	i = 0;
	command = 0;
	form_curr_path();
	signal(SIGINT, handle_sigint);
	while ((read(0, &temp, 1)) && temp != '\n')
	{
		*(save + i) = temp;
		i++;
		if (i == BUFF_SIZE)
		{
			if (!(command = ft_strjoin(command, save)))
				return (0);
			ft_memset(save, 0, BUFF_SIZE + 1);
			i = 0;
		}
	}
	*(save + i) = 0;
	if (!(command = ft_strjoin(command, save)))
		return (0);
	return (command);
}

void	handle_sigint(int sig)
{
	signal(sig, handle_sigint);
	if (!g_child_pid)
	{
		write(1, "\n", 1);
		form_curr_path();
	}
}

void	minishell(void)
{
	char	*buff;
	char	**split_buff;

	while (1)
	{
		if (!(buff = get_user_command()))
			return (void_err(0));
		if (!(split_buff = ft_splitspctab(buff)))
			return (void_err(0));
		parse_input(split_buff);
		input_clean(split_buff, buff);
	}
}
