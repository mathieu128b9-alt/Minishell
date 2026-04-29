#include "../minishell.h"

int	is_builtin(t_parser *parser)
{
	if (!parser->cmd)
		return (0);
	if (ft_strcmp(parser->cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(parser->cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(parser->cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(parser->cmd, "export") == 0)
		return (1);
	if (ft_strcmp(parser->cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(parser->cmd, "env") == 0)
		return (1);
	if (ft_strcmp(parser->cmd, "exit") == 0)
		return (1);
	return (0);
}

int	exec_builtin(t_parser *parser, t_shell *shell, t_token *token, char *imput)
{
	if (ft_strcmp(parser->cmd, "echo") == 0)
		return (ft_echo(parser));
	if (ft_strcmp(parser->cmd, "cd") == 0)
		return (ft_cd(parser, shell));
	if (ft_strcmp(parser->cmd, "pwd") == 0)
		return (ft_pwd());
	if (ft_strcmp(parser->cmd, "export") == 0)
		return (ft_export(parser, shell));
	if (ft_strcmp(parser->cmd, "unset") == 0)
		return (ft_unset(parser, shell));
	if (ft_strcmp(parser->cmd, "env") == 0)
		return (ft_env(shell));
	if (ft_strcmp(parser->cmd, "exit") == 0)
		return (ft_exit(parser, shell, token, imput));
	return (0);
}