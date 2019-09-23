#include <unistd.h>
#include <stdio.h> /* REMOVE */
#include <string.h> /* REMOVE */
#include <stdlib.h>
#include <linux/limits.h> /* CHANGE TO SOMETHING APPROPRIATE TO MAC */

#define BUFF_SIZE 4096

void	form_curr_path()
{
	char	curr_path[PATH_MAX + 3];

	getcwd(curr_path, PATH_MAX);
	strcat(curr_path, "> ");
	write(1, curr_path, strlen(curr_path));
}

char	*strjoin(char *str1, char *str2)
{
	char	*output;

	if (!str2)
		return (0);
	if (!str1)
	{
		if (!(output = (char *)malloc(strlen(str2) + 1)))
			return (0);
		strcpy(output, str2);
	}
	else
	{
		if (!(output = (char *)malloc(strlen(str1) + strlen(str2) + 1)))
			return (0);
		strcpy(output, str1);
		strcat(output, str2);
	}
	return (output);
}

char	*get_user_command()
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
			if (!(command = strjoin(command, save)))
				return (0);
			memset(save, 0, BUFF_SIZE + 1);
			i = 0;
		}
	}
	*(save + i) = 0;
	if (!(command = strjoin(command, save)))
		return (0);
	return (command);
}

int	main(int argc, char **argv)
{
	char	*buff;
	char	temp;
	int	i = 0;

	if (!(buff = get_user_command()))
		return (0);
	printf("%s", buff);
	printf(" done\n");
	free(buff);
	return (0);
}
