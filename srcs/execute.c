/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshawand <hshawand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 14:54:16 by hshawand          #+#    #+#             */
/*   Updated: 2019/10/19 12:51:42 by hshawand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		p_exec(char *path, char **buff, char mode)
{
	pid_t	pid_local;

	if (access(path, F_OK))
		return (-1);
	if (!mode && !ft_strchr(path, '/'))
		return (-1);
	pid_local = fork();
	if (!pid_local)
	{
		if (execve(path, buff, g_env) == -1)
			exit(int_err(3));
	}
	else if (pid_local < 0)
		return (int_err(4));
	g_child_pid = pid_local;
	wait(&g_child_pid);
	write(1, "\n", 1);
	g_child_pid = 0;
	return (0);
}

static int		try_run(char *path, char **buff)
{
	char	path_full[PATH_MAX];

	ft_strcpy(path_full, path);
	ft_strcat(path_full, "/");
	ft_strcat(path_full, buff[0]);
	return (p_exec(path_full, buff, 1));
}

static int		check_paths(char *path, char **buff)
{
	char	**exec_paths;
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	if (!(exec_paths = ft_strsplit(path + 5, ':')))
		ret = int_err(0);
	while (exec_paths[i] && try_run(exec_paths[i], buff))
		i++;
	if (!exec_paths[i])
		ret = -1;
	i = 0;
	while (exec_paths[i])
	{
		free(exec_paths[i]);
		i++;
	}
	free(exec_paths);
	return (ret);
}

void			execute(char **buff)
{
	int		i;

	i = 0;
	while (g_env[i] && ft_strncmp(g_env[i], "PATH=", 5))
		i++;
	if (!g_env[i] || check_paths(g_env[i], buff))
		if (p_exec(buff[0], buff, 0))
			write(2, "Not a builtin\n", 14);
}
