#include "../minishell.h"

void	free_redir(t_parser *parser)
{
	t_redir	*tmp;

	tmp = parser->redir;
	while (parser->redir)
	{
		free (parser->redir->file);
		tmp = parser->redir;
		parser->redir = parser->redir->r_next;
		free (tmp);
	}
}

void	free_tab(t_parser *parser)
{
	int	i;

	i = -1;
	while (parser->arg[++i])
		free(parser->arg[i]);
	free (parser->arg);
}

void	free_parser(t_parser *parser)
{
	t_parser	*tmp;

	while (parser)
	{
		if (parser->redir)
			free_redir(parser);
		free_tab(parser);
		free (parser->cmd);
		tmp = parser;
		parser = parser->next;
		free (tmp);
	}
}
