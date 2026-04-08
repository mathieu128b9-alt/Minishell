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
			i += len + 1;
			while (tmp[l])
			{
				res[k] = tmp[l];
				k++;
				l++;
			}
			while (parser->arg[j][i])
				res[k++] = parser->arg[j][i++];
			break;
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
	int	len;
	char *res;

	len = ft_strlen(var);
	i = 0;
	if (len == 1)
	{
		res = malloc (sizeof(char) * 2);
		res[0] = '$';
		res[1] = '\0';
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

static int	count_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ((str[i] >= 'a' && str[i] <= 'z')\
		|| (str[i] >= 'A' && str[i] <= 'Z')\
		|| (str[i] == '_') || (str[i] >= '0' && str[i] <= '9')))
		i++;
	return (i);
}

void	special_var(t_parser *parser, int j)
{
	char	*tmp;
	char	*new;
	int		i;
	int		new_size;
	int		k;

	i = 0;
	k = 0;
	tmp = ft_itoa(last_cmd_result);
	new_size = ft_strlen(tmp) + ft_strlen(parser->arg[j]) - 2;
	new = malloc(sizeof(char) * new_size + 1);
	while (parser->arg[j][i])
	{
		if (parser->arg[j][i] == '$')
		{
			if (parser->arg[j][i + 1] == '?')
			{
				i += 2;
				new_size = 0;
				while (tmp[new_size])
				{
					new[k] = tmp[new_size];
					k++;
					new_size++;
				}
			}
		}
		else
		{
			new[k] = parser->arg[j][i];
			k++;
		}
		i++;
	}
	free (parser->arg[j]);
	free(tmp);
	parser->arg[j] = new;
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
		var = NULL;
		while (parser->arg[j][i])
		{
			if (parser->arg[j][i] == '\'')
				len++;
			if (parser->arg[j][i] == '$' && len % 2 == 0)
			{
				i++;
				if (parser->arg[j][i] == '?')
				{
					special_var(parser, j);
					break;
				}
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
		if (parser->arg[j][i] == '\0')
		{
			free(tmp);
			free(var);
			var = ft_strdup(parser->arg[j]);
			free(parser->arg[j]);
			parser->arg[j] = filter_dup(var);
			free (var);
			j++;
		}
		i = 0;
	}
}
