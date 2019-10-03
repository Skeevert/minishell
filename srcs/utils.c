#include "minishell.h"

char	*get_homedir(char *path)
{
	int		i;

	i = 0;
	while (g_env[i] && ft_strncmp(g_env[i], "HOME=", 5))
		i++;
	ft_strcpy(path, g_env[i] + 5);
	return(path);
}

void	rel_to_home(char **buff)
{
	char	*path_new;

	if(!(path_new = (char *)malloc(PATH_MAX + 1)))
		return ;
	get_homedir(path_new);
	if (ft_strcmp(buff[1], "~") && (ft_strcmp(buff[1], "~/")))
		ft_strcat(path_new, buff[1] + 1);
	free(buff[1]);
	buff[1] = path_new;
	builtin_cd(buff);
}
