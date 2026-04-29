#include "../minishell.h"

long	ft_atoi_long(const char *nptr)
{
	long	res;
	long	sign;

	res = 0;
	sign = 1;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == ' ')
		nptr++;
	if (*nptr == '+' || *nptr == '-')
		if (*nptr++ == '-')
			sign = -1;
	while (*nptr >= '0' && *nptr <= '9')
		res = res * 10 + (*nptr++ - '0');
	return (res * sign);
}

int	ft_isaint(char *tmp)
{
	int		i;
	long	nb;

	i = 0;
	if (tmp[i] == '+' || tmp[i] == '-')
		i++;
	if (!tmp[i])
		return (0);
	while (tmp[i])
	{
		if (!ft_isdigit(tmp[i]))
			return (0);
		i++;
	}
	nb = ft_atoi_long(tmp);
	if (nb < INT_MIN || nb > INT_MAX)
		return (0);
	return (1);
}

int	ft_exit(t_parser *parser, t_shell *shell, t_token *token, char *imput)
{
	int	code;

	ft_putstr_fd("exit\n", 1);
	if (!parser->arg[1])
	{
		code = shell->exit_status;
		free_all(parser, shell, token, imput);
		exit (code);
	}
	if (!ft_isaint(parser->arg[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(parser->arg[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		free_all(parser, shell, token, imput);
		exit(2);
	}
	if (parser->arg[2])
		return (ft_putstr_fd("minishell: exit: too many arguments\n", 2), 1);
	code = ft_atoi(parser->arg[1]) % 256;
	free_all(parser, shell, token, imput);
	exit (code);
	return (0);
}