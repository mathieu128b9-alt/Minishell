#include "../minishell.h"

int	ft_echo(t_parser *parser)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (parser->arg[1] && ft_strcmp(parser->arg[1], "-n") == 0)
	{
		newline = 0;
		i = 2;
	}
	while (parser->arg[i])
	{
		ft_putstr_fd(parser->arg[i], 1);
		if (parser->arg[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (newline)
		ft_putstr_fd("\n",1);
	return (0);
}