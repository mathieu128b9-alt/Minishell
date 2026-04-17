#include "../minishell.h"

void	pass_word(int *temp, int *count, t_token *token)
{
	while (token[*temp].type == TOKEN_WORD)
	{
		(*temp)++;
		(*count)++;
	}
}

void	attrib_pipe(t_parser **current, t_redir **current_redir, int *nb)
{
	(*current)->next = new_node();
	(*current) = (*current)->next;
	(*current_redir) = NULL;
	(*nb)++;
}

void	attrib_redir(t_parser *current, t_redir\
	**current_redir, t_token *token, int *nb)
{
	if (current->redir == NULL)
	{
		current->redir = which_type(token, nb);
		(*current_redir) = current->redir;
	}
	else
	{
		(*current_redir)->r_next = which_type(token, nb);
		(*current_redir) = (*current_redir)->r_next;
	}
}

int	is_redirect(t_token *token, int	*nb)
{
	if (token[*nb].type == TOKEN_IN || token[*nb].type == TOKEN_OUT
		|| token[*nb].type == TOKEN_APPEND || token[*nb].type == TOKEN_HEREDOC)
		return (1);
	return (0);
}
