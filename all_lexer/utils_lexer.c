
#include "../minishell.h"

int	is_space(char c)
{
	if (c == '\t' || c == '\n' || c == '\r' || c == ' ')
		return (1);
	else
		return (0);
}

void	case_error(char *imput, t_token *token,
	char *message_erroor, int nb_token)
{
	int	i;

	nb_token = how_many_tokens(imput);
	i = 0;
	while (i < nb_token)
	{
		free(token[i].content);
		i++;
	}
	free(token);
	free(imput);
	printf("%s\n", message_erroor);
}

void	case_continue(char *imput, t_token *token, char *message_erroor)
{
	free(token);
	free(imput);
	printf("%s\n", message_erroor);
}

void	end_prog(char *imput, t_token *token, int nb_token)
{
	int	i;

	nb_token = how_many_tokens(imput);
	i = 0;
	while (i < nb_token)
	{
		free(token[i].content);
		i++;
	}
	free(token);
	free(imput);
	exit (0);
}

void	free_token(char *imput, t_token *token, int nb_token)
{
	int	i;

	nb_token = how_many_tokens(imput);
	i = 0;
	while (i < nb_token)
	{
		free(token[i].content);
		i++;
	}
	free(token);
	free(imput);
}
