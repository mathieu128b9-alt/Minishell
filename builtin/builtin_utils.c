#include "../minishell.h"

int	find_env(char **envp, char *var)
{
	int	i;
	int	len;
	char	*equal;

	equal = ft_strchr(var, '=');
	if (equal)
		len = equal - var;
	else
		len = ft_strlen(var);
	i = -1;
	while (envp[++i])
		if (!ft_strncmp(envp[i], var, len) &&  envp[i][len] == '=')
			return (i);
	return (-1);
}

int ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

char	**add_env(char **envp, char *var)
{
	char	**new_envp;
	int		size;
	int		i;

	size = 0;
	while (envp[size])
		size++;
	new_envp = malloc(sizeof(char *) * (size + 2));
	if (!new_envp)
		return (NULL);
	i = -1;
	while (envp[++i])
		new_envp[i] = ft_strdup(envp[i]);
	new_envp[i++] = ft_strdup(var);
	new_envp[i] = NULL;
	free_tab_(envp);
	return (new_envp);
}

char	**change_var(char **envp, char *var, int i_envp)
{
	if (i_envp != -1)
	{
		free(envp[i_envp]);
		envp[i_envp] = ft_strdup(var);
		return (envp);
	}
	return (add_env(envp, var));
}
