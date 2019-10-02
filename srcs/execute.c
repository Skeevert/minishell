#include "minishell.h"

void	handle_proc(int sig)
{
/*	kill(g_child_pid, SIGINT); */
	signal(sig, handle_proc);
}

void	execute(char **buff)
{
	pid_t	pid_local;

	pid_local = fork();
	signal(SIGINT, handle_proc);
	if (!pid_local)
	{
		if (execve(buff[0], buff, g_env) == -1)
			return ; /* Permission denied */
	}
	else if (pid_local < 0)
		return ; /* Fork failure */
	g_child_pid = pid_local;
	wait(&g_child_pid);
	g_child_pid = 0;
}
