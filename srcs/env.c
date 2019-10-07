/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshawand <hshawand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 14:51:46 by hshawand          #+#    #+#             */
/*   Updated: 2019/10/07 14:53:55 by hshawand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_unsetenv(char **buff)
{
	int		i;
	char	*to_free;

	i = 0;
	if (!buff[1])
		return (void_err(5));
	while (g_env[i] && ft_strncmp(g_env[i], buff[1], ft_strlen(buff[1])))
		i++;
	if (!g_env[i])
		return (void_err(4));
	to_free = g_env[i];
	while (g_env[i])
	{
		g_env[i] = g_env[i + 1];
		i++;
	}
	free(to_free);
}

void	add_env(char *new)
{
	char	**new_env;
	size_t	size;

	size = 0;
	while (g_env[size])
		size++;
	if (!(new_env = (char **)malloc(sizeof(char *) * (size + 2))))
		return (void_err(0));
	size = 0;
	while (g_env[size])
	{
		new_env[size] = g_env[size];
		size++;
	}
	if (!(new_env[size] = ft_strdup(new)))
		return (void_err(0));
	new_env[size + 1] = 0;
	free(g_env);
	g_env = new_env;
}

void	builtin_setenv(char **buff)
{
	int		i;
	char	*del;

	i = 0;
	if (!buff[1] || buff[2])
		return (void_err(5));
	del = ft_strchr(buff[1], '=');
	if (!del)
		return (void_err(5));
	while (g_env[i] && ft_strncmp(g_env[i], buff[1], del - buff[1]))
		i++;
	if (g_env[i])
	{
		free(g_env[i]);
		if (!(g_env[i] = ft_strdup(buff[1])))
			return (void_err(0));
	}
	else
		add_env(buff[1]);
}

void	builtin_env(void)
{
	int		i;

	i = 0;
	while (g_env[i])
	{
		ft_putstr(g_env[i]);
		write(1, "\n", 1);
		i++;
	}
}
