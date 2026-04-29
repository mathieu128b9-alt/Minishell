#include "../minishell.h"

int	ft_env(t_shell *shell)
{
	int	i;

	if (!shell->envp)
		return (1);
	i = -1;
	while (shell->envp[++i])
	{
		ft_putstr_fd(shell->envp[i], 1);
		ft_putstr_fd("\n", 1);
	}
	return (0);
}