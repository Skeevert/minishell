#include "minishell.h"

void	input_clean(char **arr, char *str)
{
	int		i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	free(str);
}

int		main(void)
{
	char	*buff;
	char	**split_buff; /* FREE */

	while (1)
	{
		if (!(buff = get_user_command()))
			return (0);
		if (!(split_buff = ft_splitspctab(buff)))
			return (0);
		parse_input(split_buff);
		input_clean(split_buff, buff);
	}
	return (0);
}
