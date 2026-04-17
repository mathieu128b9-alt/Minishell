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
	temp->heredoc_fd = -1;
	(*nb)++;
	return (temp);
}

void	arg_after_cmd(t_token *token, t_parser *current, int *nb)
{
	int	temp;
	int	count;

	count = 0;
	temp = *nb;
	pass_word(&temp, &count, token);
	current->arg = malloc(sizeof(char *) * (count + 2));
	if (!current->arg)
		return ;
	count = 0;
	if (current->cmd == NULL)
		current->arg[count] = NULL;
	else
		current->arg[count] = ft_strdup(current->cmd);
	count++;
	while (*nb != temp)
	{
		current->arg[count] = ft_strdup(token[*nb].content);
		count++;
		(*nb)++;
	}
	current->arg[count] = NULL;
}

void	try_path(t_parser *current, t_token *token, int *nb, t_shell *shell)
{
	current->cmd = get_path(token[*nb].content, shell->envp);
	(*nb)++;
	arg_after_cmd(token, current, nb);
}

int	cmd_or_file(t_token *token, t_parser *current, int *nb, t_shell *shell)
{
	int	test;
	int	index;

	index = *nb;
	if (*nb == 0)
		try_path(current, token, nb, shell);
	else if (*nb - 1 >= 0)
	{
		test = *nb - 1;
		if (is_redirect(token, &test) == 0)
			try_path(current, token, nb, shell);
	}
	if (current->cmd == NULL)
	{
		ft_putstr_fd(token[index].content, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	return (0);
}

t_parser	*create_parser(t_token *token, t_shell *shell)
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
		{
			if (cmd_or_file(token, current, &nb, shell) == 1)
				return (free(parser), NULL);
		}
		else if (is_redirect(token, &nb) == 1)
			attrib_redir(current, &current_redir, token, &nb);
		else if (token[nb].type == TOKEN_PIPE)
			attrib_pipe(&current, &current_redir, &nb);
	}
	return (parser);
}
