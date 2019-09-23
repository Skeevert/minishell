#include <unistd.h>
#include <stdio.h> /* REMOVE */
#include <string.h> /* REMOVE */
#include <stdlib.h>

#define BUFF_SIZE 4096

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
	char	temp;
	int	i;

	temp = 0;
	i = 0;
	command = 0;
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
