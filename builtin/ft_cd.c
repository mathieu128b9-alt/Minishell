#include "../minishell.h"

int	change_pwd(t_shell *shell, char *var)
{
	char	tmp[PATH_MAX];
	char	*new_path;
	int		i;

	if (!getcwd(tmp, PATH_MAX))
		return (perror("pwd"), 2);
	new_path = ft_strjoin(var, tmp);
	if (!new_path)
		return (1);
	i = find_env(shell->envp, var);
	shell->envp = change_var(shell->envp, new_path, i);
	free(new_path);
	return (0);
}

int	ft_cd(t_parser *parser, t_shell *shell)
{
	char	*target;
	int		i;

	if (!parser->arg[1])
	{
		i = find_env(shell->envp, "HOME");
		if (i == -1)
			return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
		target = (ft_strchr(shell->envp[i], '=') + 1);
	}
	else
		target = parser->arg[1];
	if (change_pwd(shell, "OLDPWD="))
		return (1);
	if (chdir(target) == -1)
		return (perror(target), 2);
	if (change_pwd(shell, "PWD="))
		return (1);
	return (0);
}