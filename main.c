/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuter <msuter@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 14:44:47 by aroduit           #+#    #+#             */
/*   Updated: 2026/04/17 22:37:01 by msuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	testing(t_parser *parser)
// {
// 	while (parser != NULL)
// 	{
// 		int i = 0;
// 		printf("\n\n debut de ma boucle while pour les redir\n\n");
// 		while (parser->redir != NULL)
// 		{
// 			printf("\n\nprint de mon type\n\n");
// 			printf("%d\n", parser->redir->type);
// 			printf("\n\nprint de mon file\n\n");
// 			printf("%s\n", parser->redir->file);
// 			printf("nouveau noeud de mon t_redir\n");
// 			parser->redir = parser->redir->r_next;
// 		}
// 		if (parser->cmd != NULL)
// 		{
// 			printf("\n\nprint de ma cmd\n\n");
// 			printf("%s\n", parser->cmd);
// 			printf("\n\n debut de ma boucle while pour les arg\n\n");
// 			while (parser->arg[i] != NULL)
// 			{
// 				printf("\n\nprint de mes arg\n\n");
// 				printf("%s\n", parser->arg[i]);
// 				i++;
// 			}
// 		}
// 		parser = parser->next;
// 	}
// }

void	init(t_shell *shell, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	shell->envp = malloc (sizeof(char *) * (i + 1));
	i = 0;
	while (envp[i])
	{
		shell->envp[i] = ft_strdup(envp[i]);
		i++;
	}
	shell->envp[i] = NULL;
	shell->exit_status = 0;
	shell->line_num = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_token		*token;
	t_parser	*parser;
	char		*imput;
	int			verif_nb;
	t_shell		*shell;

	shell = malloc(sizeof(t_shell));
	init(shell, envp);
	(void)argc;
	(void)argv;
	while (1)
	{
		imput = readline("minishell>");
		if (!imput)
			case_error(imput, NULL, "erreur lors du malloc du imput", verif_nb);
		add_history(imput);
		verif_nb = how_many_tokens(imput);
		token = lexing(imput, verif_nb);
		if (token == NULL)
		{
			case_continue(imput, token, "erreur, il manque une quote");
			continue ;
		}
		if (ft_strncmp(token[0].content, "exit", 5) == 0)
			end_prog(imput, token, verif_nb);
		parser = create_parser(token, shell);
		// testing(parser);
		if (parser != NULL)
		{
			search_var(parser, shell);
			execute_cmd(parser, shell);
		}
		free_token(imput, token, verif_nb);
		free_parser(parser);
	}
}
