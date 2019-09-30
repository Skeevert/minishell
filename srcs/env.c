#include "minishell.h"

void	builtin_unsetenv(char **env, char **buff)
{
	int		i;
	char 	*to_free;

	i = 0;
	if (!buff[1])
		return ; /* Error */
	while (env[i] && ft_strncmp(env[i], buff[1], ft_strlen(buff[1])))
		i++;
	if(!env[i])
		return ; /* Error: can't find environment variable */
	to_free = env[i];
	while(env[i])
	{
		env[i] = env[i + 1];
		i++;
	}
	free(to_free);
}

void	add_env(char	***env, char *new)
{
	char	**new_env;
	size_t	size;

	size = 0;
	while((*env)[size])
		size++;
	if (!(new_env = (char **)malloc(sizeof(char *) * (size + 2))))
		return ;
	size = 0;
	while ((*env)[size])
	{
		new_env[size] = (*env)[size];
		size++;
	}
	if (!(new_env[size] = ft_strdup(new)))
		return ;
	new_env[size + 1] = 0;
	free(*env);
	*env = new_env;
}

void	builtin_setenv(char ***env, char **buff)
{
	int		i;
	char	*del;

	i = 0;
	if (!buff[1])
		return ; /* Error */
	del = ft_strchr(buff[1], '=');
	if (!del)
		return ; /* Error */
	while ((*env)[i] && ft_strncmp((*env)[i], buff[1], del - buff[1]))
		i++;	
	if ((*env)[i])
	{
		free((*env)[i]);
		if (!((*env)[i] = ft_strdup(buff[1])))
			return ; /* Error */
	}
	else
		add_env(env, buff[1]);
}

void	builtin_env(char **env)
{
	int		i;

	i = 0;
	while(env[i])
	{
		ft_putstr(env[i]);
		write(1, "\n", 1);
		i++;
	}
}
