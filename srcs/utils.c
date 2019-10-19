/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshawand <hshawand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 14:45:34 by hshawand          #+#    #+#             */
/*   Updated: 2019/10/19 12:34:54 by hshawand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	void_err(int code)
{
	if (code == 0)
		write(2, "Cannot allocate memory, reboot recommended\n", 43);
	else if (code == 1)
		write(2, "Not a Directory\n", 16);
	else if (code == 2)
		write(2, "Not in pwd\n", 11);
	else if (code == 3)
		write(2, "Cannot find\n", 12);
	else if (code == 4)
		write(2, "Cannot find environment variable\n", 33);
	else if (code == 5)
		write(2, "Incorrect format\n", 17);
}

int		int_err(int code)
{
	if (code == 0)
		write(2, "Cannot allocate memory, reboot recommended\n", 43);
	else if (code == 1)
		write(2, "Cannot find environment variable\n", 33);
	else if (code == 2)
		write(2, "Not a builtin\n", 14);
	else if (code == 3)
		write(2, "Permission denied\n", 18);
	else if (code == 4)
		write(2, "Fork failure\n", 13);
	return (-1);
}

int		get_val(char **buff)
{
	int			i;
	int			j;
	size_t		len;

	i = 0;
	j = 0;
	while (buff[i])
	{
		if (buff[i][0] == '$')
		{
			j = 0;
			len = ft_strlen(buff[i] + 1);
			while (g_env[j] && ft_strncmp(g_env[j], buff[i] + 1, len))
				j++;
			if (!g_env[j])
				return (int_err(1));
			free(buff[i]);
			buff[i] = ft_strdup(g_env[j] + len + 1);
		}
		i++;
	}
	return (0);
}

char	*get_homedir(char *path)
{
	int		i;

	i = 0;
	while (g_env[i] && ft_strncmp(g_env[i], "HOME=", 5))
		i++;
	g_env[i] ? ft_strcpy(path, g_env[i] + 5) : 0;
	return (path);
}

void	rel_to_home(char **buff)
{
	char	*path_new;

	if (!(path_new = (char *)malloc(PATH_MAX + 1)))
		return (void_err(0));
	get_homedir(path_new);
	if (ft_strcmp(buff[1], "~") && (ft_strcmp(buff[1], "~/")))
		ft_strcat(path_new, buff[1] + 1);
	free(buff[1]);
	buff[1] = path_new;
	builtin_cd(buff);
}
