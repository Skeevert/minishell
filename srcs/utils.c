#include "minishell.h"

char	*get_user(char **envp, char *user)
{
	int		i;

	i = 0;
	ft_bzero(user, 33);
	while (envp[i] && ft_strncmp(envp[i], "USER=", 5))
		i++;
	ft_strcpy(user, envp[i] + 5);
	return(user);
}

char	*get_homedir(char **envp, char *path)
{
	char	user[33];

	get_user(envp, user);
	ft_strcpy(path, "/Users/");
	ft_strcat(path, user);
	return(path);
}

void	rel_to_home(char **envp, char **buff)
{
	char	*path_new;

	if(!(path_new = (char *)malloc(PATH_MAX + 1)))
		return ;
	get_homedir(envp, path_new);
	if (ft_strcmp(buff[1], "~") && (ft_strcmp(buff[1], "~/")))
		ft_strcat(path_new, buff[1] + 1);
	free(buff[1]);
	buff[1] = path_new;
	builtin_cd(buff, envp);
}
