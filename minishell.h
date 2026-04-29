#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/types.h>
# include <dirent.h>
# include <string.h>
# include <sys/ioctl.h>
# include "libft/libft.h"

# define INT_MAX				2147483647
# define INT_MIN				-2147483648

typedef enum e_token
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_IN,
	TOKEN_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_END,
}	t_enum_token;

typedef struct t_token
{
	t_enum_token	type;
	char			*content;
}	t_token;

typedef struct t_contexte
{
	int	i;
	int	size_word;
	int	nb;
}	t_contexte;

typedef enum t_enum_redir
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
}	t_enum_redir;

typedef struct t_redir	t_redir;
typedef struct t_redir
{
	int		type;
	int		heredoc_fd;
	char	*file;
	t_redir	*r_next;
}	t_redir;

typedef struct t_parser	t_parser;
typedef struct t_parser
{
	char		*cmd;
	char		**arg;
	t_redir		*redir;
	t_parser	*next;
}	t_parser;

typedef struct s_shell
{
	char	**envp;
	int		exit_status;
	int		line_num;
	int		shell_lvl;
}	t_shell;

//! fonctions generales
void		case_error(char *imput, t_token *token,
				char *message_erroor, int nb_token);
void		case_continue(char *imput, t_token *token, char *message_erroor);
//void		end_prog(char *imput, t_token *token, int nb_token);
void		free_token(char *imput, t_token *token);

//! fonctions lexer
int			is_space(char c);
int			how_many_tokens(char *imput);
int			case_word(char *imput, t_contexte *c);
t_token		*lexing(char *imput, int verif_nb);
void		case_in_or_heredoc(char *imput, t_contexte *c, t_token *token);
void		case_out_or_happend(char *imput, t_contexte *c, t_token *token);

//! fonctions parser
int			is_redirect(t_token *token, int	*nb);
t_parser	*new_node(void);
t_redir		*new_redir_node(void);
t_redir		*attach_redir_node(t_redir *current);
t_parser	*create_parser(t_token *token, t_shell *shell);
char		*get_path(char *cmd, char **envp);
void		free_parser(t_parser *parser);
void		attrib_redir(t_parser *current, t_redir\
	**current_redir, t_token *token, int *nb);
void		attrib_pipe(t_parser **current, t_redir **current_redir, int *nb);
t_redir		*which_type(t_token *token, int *nb);
void		pass_word(int *temp, int *count, t_token *token);

//! fonctions expander
void		search_var(t_parser *parser, t_shell *shell);
char		*filter_dup(char *content);

//! fonctions builtin
int			find_env(char **envp, char *var);
int			ft_strcmp(const char *s1, const char *s2);
int			is_builtin(t_parser *parser);
int			exec_builtin(t_parser *parser, t_shell *shell, t_token *token, char *imput);
int			ft_cd(t_parser *parser, t_shell *shell);
int			ft_echo(t_parser *parser);
int			ft_env(t_shell *shell);
int			ft_exit(t_parser *parser, t_shell *shell, t_token *token, char *imput);
int 		ft_export(t_parser *parser, t_shell *shell);
int			ft_pwd(void);
int			ft_unset(t_parser *parser, t_shell *shell);
char		**change_var(char **envp, char *var, int i_envp);

//! fonction exec
void		exec_redir(t_redir *redir);
int			execute_cmd(t_parser *parser, t_shell *shell, t_token *token, char *imput);
int			perror_return(char *msg, int ret);
int			prepare_heredocs(t_parser *parser, t_shell *shell);
void		free_tab_(char **tab);

//! fonction free
void		free_all(t_parser *parser, t_shell *shell, t_token *token, char *imput);
void		free_shell(t_shell *shell);

#endif