#include "minishell.h"

int		p_exec(char *path, char **buff)
{
	pid_t	pid_local;

	if (access(path, 1))
		return (-1);
	pid_local = fork();
	signal(SIGINT, handle_sigint);
	if (!pid_local)
	{
		if (execve(path, buff, g_env) == -1)
			return (-1); /* Permission denied */
	}
	else if (pid_local < 0)
		return (-1); /* Fork failure */
	g_child_pid = pid_local;
	wait(&g_child_pid);
	g_child_pid = 0;
	return (0);
}

int		try_run(char *path, char **buff)
{
	char	path_full[PATH_MAX];

	ft_strcpy(path_full, path);
	ft_strcat(path_full, "/");
	ft_strcat(path_full, buff[0]);
	return p_exec(path_full, buff);
}

void	execute(char **buff)
{
	char	**exec_paths;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (ft_strncmp(g_env[i], "PATH=", 5))
		i++;
	if (!(exec_paths = ft_strsplit(g_env[i] + 5, ':')))
		return ; /* Malloc error */
	while (exec_paths[j] && try_run(exec_paths[j], buff))
		j++;
	if (!exec_paths[j])
		if(p_exec(buff[0], buff))
			return ;
	j = 0;
	while (exec_paths[j])
	{
		free(exec_paths[j]);
		j++;
	}
	free(exec_paths);
}
