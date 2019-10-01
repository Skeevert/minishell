#include "minishell.h"

void	parse_input(char **buff)
{
	if (!buff || !buff[0])
		return ;
	if (!(ft_strcmp(buff[0], "cd")))
		builtin_cd(buff);
	else if (!(ft_strcmp(buff[0], "echo")))
		builtin_echo(buff);
	else if (!(ft_strcmp(buff[0], "setenv")))
		builtin_setenv(buff);
	else if (!(ft_strcmp(buff[0], "unsetenv")))
		builtin_unsetenv(buff);
	else if (!(ft_strcmp(buff[0], "env")))
		builtin_env();
	else if (!(ft_strcmp(buff[0], "exit")))
		builtin_exit(buff);
	else
		execute(buff);
}

void	form_curr_path()
{
	char	curr_path[PATH_MAX + 3];

	getcwd(curr_path, PATH_MAX);
	ft_strcat(curr_path, "> ");
	write(1, curr_path, strlen(curr_path));
}

char	*get_user_command(void)
{
	char	*command;
	char	save[BUFF_SIZE + 1];
	int	i;

	i = 0;
	command = 0;
	form_curr_path();
	while ((read(0, save + i, 1)) && *(save + i) != '\n')
	{
		i++;
		if (i == BUFF_SIZE)
		{
			if (!(command = ft_strjoin(command, save)))
				return (0);
			ft_memset(save, 0, BUFF_SIZE + 1);
			i = 0;
		}
	}
	*(save + i) = 0;
	if (!(command = ft_strjoin(command, save)))
		return (0);
	return (command);
}

void	handle_sigint(int sig)
{
	(void)sig;
	kill(g_child_pid, SIGINT);
	/*
	write(1, "\n", 1);
	return minishell();
	*/
}

void	minishell()
{
	char	*buff;
	char	**split_buff;

	signal(SIGINT, handle_sigint);
	while (1)
	{
		if (!(buff = get_user_command()))
			return ;
		if (!(split_buff = ft_splitspctab(buff)))
			return ;
		parse_input(split_buff);
		input_clean(split_buff, buff);
	}
}
