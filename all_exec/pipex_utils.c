#include "../minishell.h"

char	*get_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	char	*env;
	int		i;

	if (ft_strchr(cmd, '/'))
	{
		if (!access(cmd, X_OK))
			return (ft_strdup(cmd));
		return (NULL);
	}
	env = get_env_path(envp);
	if (!env)
		return (NULL);
	paths = ft_split(env, ':');
	i = -1;
	while (paths[++i])
	{
		path = build_path(paths[i], cmd);
		if (path && !access(path, X_OK))
			return (free_tab(paths), path);
		free(path);
	}
	free_tab(paths);
	return (NULL);
}

char	*get_env_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	*build_path(char *dir, char *cmd)
{
	char	*tmp;
	char	*path;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	path = ft_strjoin(tmp, cmd);
	free(tmp);
	return (path);
}

void	free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}
