#include "../minishell.h"

static void	replace(t_parser *parser, char *tmp, int j, int len)
{
	char	*res;
	int		i;
	int		k;
	int		l;

	init_replace(&i, &k, &l);
	i = ft_strlen(parser->arg[j]) + ft_strlen(tmp) - len;
	res = malloc(sizeof(char) * i + 1);
	i = 0;
	while (parser->arg[j][i])
	{
		if (parser->arg[j][i] == '$')
		{
			i += len + 1;
			while (tmp[l])
				res[k++] = tmp[l++];
			while (parser->arg[j][i])
				res[k++] = parser->arg[j][i++];
			break ;
		}
		res[k++] = parser->arg[j][i++];
	}
	res[k] = '\0';
	free(parser->arg[j]);
	parser->arg[j] = res;
}

char	*schr_in_env(char *var, char **envp)
{
	int		i;
	int		len;
	char	*res;

	len = ft_strlen(var);
	i = 0;
	if (envp == NULL || len == 1)
	{
		res = special_case(envp, len);
		return (res);
	}
	while (envp[i])
	{
		if (strncmp(var, envp[i], len) == 0)
		{
			res = ft_substr(envp[i], len, ft_strlen(envp[i]) - len);
			return (res);
		}
		i++;
	}
	res = malloc (sizeof(char) * 1);
	res[0] = '\0';
	return (res);
}

int	count_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ((str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= 'A' && str[i] <= 'Z')
			|| (str[i] == '_') || (str[i] >= '0' && str[i] <= '9')))
		i++;
	return (i);
}

void	special_var(t_parser *parser, int j, t_shell *shell)
{
	char	*tmp;
	char	*new;
	int		i;
	int		new_size;
	int		k;

	i = -1;
	k = 0;
	tmp = ft_itoa(shell->exit_status);
	new_size = ft_strlen(tmp) + ft_strlen(parser->arg[j]) - 2;
	new = malloc(sizeof(char) * new_size + 1);
	while (parser->arg[j][++i])
	{
		if (case_interrog(parser, &new_size, &i, &j) == 1)
		{
			ft_memcpy(new + k, tmp, ft_strlen(tmp));
			k += ft_strlen(tmp);
		}
		else
			new[k++] = parser->arg[j][i];
	}
	new[k - 1] = '\0';
	free (parser->arg[j]);
	free(tmp);
	parser->arg[j] = new;
}

void	search_var(t_parser *parser, t_shell *shell)
{
	t_var	var;

	var.i = 0;
	var.j = 0;
	while (parser->arg[var.j])
	{
		var.len = 0;
		var.tmp = NULL;
		var.var = NULL;
		while (parser->arg[var.j][var.i])
		{
			if (verif_and_schr_in_env(parser, &var, shell) == 1)
				break ;
		}
		if (var.tmp != NULL)
			replace(parser, var.tmp, var.j, var.len);
		if (parser->arg[var.j][var.i] == '\0')
			free_my_var(parser, &var);
		var.i = 0;
	}
}
