#include "minishell.h"

char**	form_env(char **envp)
{
	char	**new_env;
	size_t	size;

	size = 0;
	while(envp[size])
		size++;
	if (!(new_env = (char **)malloc(sizeof(char *) * (size + 1))))
		return (0);
	size = 0;
	while (envp[size])
	{
		if (!(new_env[size] = ft_strdup(envp[size])))
			return (0);
		size++;
	}
	new_env[size] = 0;
	return (new_env);
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

void	env_clean(char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

int		main(int argc, char **argv, char **envp)
{
	char	*buff;
	char	**split_buff; /* FREE */
	char	**dynamic_env;

	if(!(dynamic_env = form_env(envp)))
		return (0); /* Error */
	while (1)
	{
		if (!(buff = get_user_command()))
			return (0);
		if (!(split_buff = ft_splitspctab(buff)))
			return (0);
		parse_input(split_buff, &dynamic_env);
		input_clean(split_buff, buff);
	}
	env_clean(dynamic_env);
	(void)argc;
	(void)argv;
	return (0);
}
