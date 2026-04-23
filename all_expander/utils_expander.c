#include "../minishell.h"

void	free_my_var(t_parser *parser, t_var *var)
{
	free(var->tmp);
	free(var->var);
	var->var = ft_strdup(parser->arg[var->j]);
	free(parser->arg[var->j]);
	parser->arg[var->j] = filter_dup(var->var);
	free (var->var);
	var->j++;
}

int	verif_and_schr_in_env(t_parser *parser, t_var *var, t_shell *shell)
{
	if (parser->arg[var->j][var->i] == '\'')
		var->len++;
	if (parser->arg[var->j][var->i] == '$' && var->len % 2 == 0)
	{
		var->i++;
		if (parser->arg[var->j][var->i] == '?')
		{
			special_var(parser, var->j, shell);
			return (1);
		}
		var->len = count_len(parser->arg[var->j] + var->i);
		var->tmp = ft_substr(parser->arg[var->j], var->i, var->len);
		var->var = ft_strjoin(var->tmp, "=");
		free (var->tmp);
		var->tmp = schr_in_env(var->var, shell->envp);
		return (1);
	}
	var->i++;
	return (0);
}

void	init_replace(int *i, int *k, int *l)
{
	*i = 0;
	*k = 0;
	*l = 0;
}

char	*special_case(char **envp, int len)
{
	char	*res;

	if (envp == NULL)
	{
		res = malloc (sizeof(char) * 1);
		res[0] = '\0';
	}
	if (len == 1)
	{
		res = malloc (sizeof(char) * 2);
		res[0] = '$';
		res[1] = '\0';
	}
	return (res);
}

int	case_interrog(t_parser *parser, int *new_size, int *i, int *j)
{
	if (parser->arg[*j][*i] == '$')
	{
		if (parser->arg[*j][(*i) + 1] == '?')
		{
			if (parser->arg[*j][(*i) + 2] != '\0')
				(*i) += 2;
			*new_size = 0;
			return (1);
		}
	}
	return (0);
}
