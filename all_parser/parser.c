
#include "../minishell.h"

t_redir	*which_type(t_token *token, int *nb)
{
	t_redir	*temp;

	temp = new_redir_node();
	if (token[*nb].type == TOKEN_IN)
		temp->type = REDIR_IN;
	else if (token[*nb].type == TOKEN_OUT)
		temp->type = REDIR_OUT;
	else if (token[*nb].type == TOKEN_APPEND)
		temp->type = REDIR_APPEND;
	else
		temp->type = REDIR_HEREDOC;
	(*nb)++;
	temp->file = ft_strdup(token[*nb].content);
	(*nb)++;
	return (temp);
}

void	arg_after_cmd(t_token *token, t_parser *current, int *nb)
{
	int	temp;
	int	count;

	count = 0;
	temp = *nb;
	while (token[temp].type == TOKEN_WORD)
	{
		temp++;
		count++;
	}
	current->arg = malloc(sizeof(char *) * (count + 2));
	if (!current->arg)
		return ;
	count = 0;
	current->arg[count] = ft_strdup(current->cmd);
	count++;
	while(*nb != temp)
	{
		current->arg[count] = ft_strdup(token[*nb].content);
		count++;
		(*nb)++;
	}
	current->arg[count] = NULL;
}

void	cmd_or_file(t_token *token, t_parser *current, int *nb)
{
	int	test;

	if (*nb == 0)
	{
		current->cmd = ft_strdup(token[*nb].content);
		(*nb)++;
		arg_after_cmd(token, current, nb);
	}
	else if (*nb - 1 >= 0)
	{
		test = *nb - 1;
		if (is_redirect(token, &test) == 0)
		{
			current->cmd = ft_strdup(token[*nb].content);
			(*nb)++;
			arg_after_cmd(token, current, nb);
		}
	}
}

t_parser	*create_parser(t_token *token)
{
	int			nb;
	t_parser	*parser;
	t_parser	*current;
	t_redir		*current_redir;

	parser = new_node();
	current = parser;
	
	nb = 0;
	while (token[nb].type != TOKEN_END)
	{
		if (token[nb].type == TOKEN_WORD)
			cmd_or_file(token, current, &nb);
		else if (is_redirect(token, &nb) == 1)
		{
			if (current->redir == NULL)
			{
				current->redir = which_type(token, &nb);
				current_redir = parser->redir;
			}
			else
			{
				current_redir->r_next = which_type(token, &nb);
				current_redir = current_redir->r_next;
			}
		}
		else if (token[nb].type == TOKEN_PIPE)
		{
			current->next = new_node();
			current = current->next;
			current_redir = NULL;
			nb++;
		}
	}
	return (parser);
}