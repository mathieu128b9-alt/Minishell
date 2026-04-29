#include "../minishell.h"

char	**rm_env(char **envp, int i_envp)
{
	char	**new_envp;
	int		j;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	new_envp = malloc(sizeof(char *) * i);
	if (!new_envp)
		return (NULL);
	i = -1;
	j = 0;
	while (envp[++i])
		if (i != i_envp)
			new_envp[j++] = ft_strdup(envp[i]);
	new_envp[j] = NULL;
	free_tab_(envp);
	return (new_envp);
}

int	ft_unset(t_parser *parser, t_shell *shell)
{
	int		i;
	int		i_envp;
	char	**tmp;

	if (!parser->arg[1])
		return (0);
	i = 0;
	while (parser->arg[++i])
	{
		i_envp = find_env(shell->envp, parser->arg[i]);
		if (i_envp != -1)
		{
			tmp = rm_env(shell->envp, i_envp);
			if (!tmp)
				return (1);
			shell->envp = tmp;
		}
	}
	return (0);
}