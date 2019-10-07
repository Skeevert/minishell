/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshawand <hshawand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 14:46:51 by hshawand          #+#    #+#             */
/*   Updated: 2019/10/07 14:47:56 by hshawand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**form_env(char **envp)
{
	size_t	size;

	size = 0;
	while (envp[size])
		size++;
	if (!(g_env = (char **)malloc(sizeof(char *) * (size + 1))))
		return (0);
	size = 0;
	while (envp[size])
	{
		if (!(g_env[size] = ft_strdup(envp[size])))
			return (0);
		size++;
	}
	g_env[size] = 0;
	return (g_env);
}

void	input_clean(char **arr, char *str)
{
	int		i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	i = 0;
	free(arr);
	free(str);
}

void	env_clean(void)
{
	int		i;

	i = 0;
	while (g_env[i])
	{
		free(g_env[i]);
		i++;
	}
	free(g_env);
}

int		main(int argc, char **argv, char **envp)
{
	if (!(g_env = form_env(envp)))
		return (int_err(0));
	minishell();
	env_clean();
	(void)argc;
	(void)argv;
	return (0);
}
