#include "../minishell.h"

int	ft_export_display(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->envp[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(shell->envp[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
	return (0);
}

int ft_export(t_parser *parser, t_shell *shell)
{
	int		i;
	int		i_envp;
	char	**tmp;

	if (!parser->arg[1])
		return (ft_export_display(shell));
	i = 0;
	while (parser->arg[++i])
	{
		i_envp = find_env(shell->envp, parser->arg[i]);
		tmp = change_var(shell->envp, parser->arg[i], i_envp);
		if (!tmp)
			return (1);
		shell->envp = tmp;
	}
	return (0);
}
