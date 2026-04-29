#include "../minishell.h"

int	ft_pwd(void)
{
	char	buf[PATH_MAX];

	if (!getcwd(buf, PATH_MAX))
		return (perror("pwd"), 2);
	ft_putstr_fd(buf, 1);
	ft_putstr_fd("\n", 1);
	return (0);
}