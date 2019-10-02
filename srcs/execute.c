#include "minishell.h"

void	execute(char **buff)
{
	pid_t	pid_local;

	pid_local = fork();
	if (!pid_local)
	{
		if (execve(buff[0], buff, g_env) == -1)
			return ; /* Permission denied */
	}
	else if (pid_local < 0)
		return ; /* Fork failure */
	else
	{
		g_child_pid = pid_local;
		signal(SIGINT, handle_sigint);
		wait(&g_child_pid);
		g_child_pid = 0;
	}
}
