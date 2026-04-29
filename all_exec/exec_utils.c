#include "../minishell.h"

void	free_redir(t_parser *parser)
{
	t_redir	*tmp;

	while (parser->redir)
	{
		if (parser->redir->file)
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
	if (!parser->arg)
		return ;
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
		if (parser->arg)
			free_tab(parser);
		if (parser->cmd)
			free (parser->cmd);
		tmp = parser;
		parser = parser->next;
		free (tmp);
	}
}

void	free_shell(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->envp)
		free_tab_(shell->envp);
	free (shell);
}

void	free_all(t_parser *parser, t_shell *shell, t_token *token, char *imput)
{
	free_shell(shell);
	free_parser(parser);
	free_token(imput, token);
}

int	perror_return(char *msg, int ret)
{
	perror(msg);
	return (ret);
}

void	free_token(char *imput, t_token *token)
{
	int	i;

	i = -1;
	while (token[++i].type != TOKEN_END)
		free(token[i].content);
	free(token);
	free(imput);
}
