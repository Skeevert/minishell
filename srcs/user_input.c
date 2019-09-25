#include "minishell.h"

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

