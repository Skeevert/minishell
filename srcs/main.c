#include "minishell.h"

int	main(void)
{
	char	*buff;

	while (1)
	{
		if (!(buff = get_user_command()))
			return (0);
		ft_putstr(buff);
		ft_putstr(" catched\n");
		free(buff);
	}
	return (0);
}
