#include "../minishell.h"

static void	replace(t_parser *parser, char *tmp, int j, int len)
{
	char	*res;
	int		new_size;
	int		i;
	int		k;
	int		l;

	k = 0;
	i = 0;
	l = 0;
	new_size = ft_strlen(parser->arg[j]) + ft_strlen(tmp) - len;
	res = malloc(sizeof(char) * new_size + 1);
	while(parser->arg[j][i])
	{
		if (parser->arg[j][i] == '$')
		{
			i += len;
			while (tmp[l])
			{
				res[k] = tmp[l];
				k++;
				l++;
			}
		}
		else
		{
			res[k] = parser->arg[j][i];
			k++;
		}
		i++;
	}
	res[k] = '\0';
	free(parser->arg[j]);
	parser->arg[j] = res;
}

static char	*schr_in_env(char *var, char **envp)
{
	int	i;
	int	j;
	int	len;
	char *res;

	len = ft_strlen(var);
	i = 0;
	j = 0;
	while (envp[i])
	{
		if (strncmp(var, envp[i], len) == 0)
		{
			res = ft_substr(envp[i], len, ft_strlen(envp[i]) - len);
			return (res);
		}
		i++;
	}
	return ("");
}

static int	count_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] >= 'a' && str[i] <= 'z'\
		|| str[i] >= 'A' && str[i] <= 'Z'\
		|| str[i] == '_' || str[i] >= '0' && str[i] <= '9'))
		i++;
	return (i);
}

void	search_var(t_parser *parser, char **envp)
{
	int		i;
	int		j;
	int		len;
	char	*var;
	char	*tmp;

	i = 0;
	j = 0;
	while(parser->arg[j])
	{
		len = 0;
		tmp = NULL;
		while (parser->arg[j][i])
		{
			if (parser->arg[j][i] == '\'')
				len++;
			if (parser->arg[j][i] == '$' && len % 2 == 0)
			{
				i++;
				len = count_len(parser->arg[j] + i);
				tmp = ft_substr(parser->arg[j], i, len);
				var = ft_strjoin(tmp, "=");
				free (tmp);
				tmp = schr_in_env(var, envp);
				break;
			}
			i++;
		}
		if (tmp != NULL)
			replace(parser, tmp, j, len);
		j++;
		i = 0;
	}
}