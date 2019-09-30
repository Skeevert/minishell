#include "minishell.h"

char	*get_user(char **env, char *user)
{
	int		i;

	i = 0;
	ft_bzero(user, 33);
	while (env[i] && ft_strncmp(env[i], "USER=", 5))
		i++;
	ft_strcpy(user, env[i] + 5);
	return(user);
}

char	*get_homedir(char **env, char *path)
{
	char	user[33];

	get_user(env, user);
	ft_strcpy(path, "/Users/");
	ft_strcat(path, user);
	return(path);
}

void	rel_to_home(char **env, char **buff)
{
	char	*path_new;

	if(!(path_new = (char *)malloc(PATH_MAX + 1)))
		return ;
	get_homedir(env, path_new);
	if (ft_strcmp(buff[1], "~") && (ft_strcmp(buff[1], "~/")))
		ft_strcat(path_new, buff[1] + 1);
	free(buff[1]);
	buff[1] = path_new;
	builtin_cd(buff, env);
}
