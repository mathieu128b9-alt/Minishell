#include "../minishell.h"

int	child_process(t_parser *current, int fd[2], int *prev_fd, t_shell *shell)
{
	if (*prev_fd != -1)
	{
		dup2(*prev_fd, STDIN_FILENO);
		close(*prev_fd);
	}
	if (current->next)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
	}
	if (current->redir)
		exec_redir(current->redir);
	// if (is_builtin(current))
	// 	exit (exec_builtin(current, shell));
	if (current->cmd == NULL)
	{
		shell->exit_status = 127;
		exit(127);
	}
	execve(current->arg[0], current->arg, shell->envp);
	perror(current->arg[0]);
	exit(127);
}

void	parent_process(t_parser *current, int fd[2], int *prev_fd)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (current->next)
	{
		close(fd[1]);
		*prev_fd = fd[0];
	}
}

int	execute_pipeline(t_parser *parser, int *prev_fd, t_shell *shell)
{
	t_parser	*current;
	pid_t		pid;
	int			fd[2];
	int			status;

	status = 0;
	current = parser;
	while (current)
	{
		if (current->next && pipe(fd) == -1)
			return (perror_return("pipe", 1));
		pid = fork();
		if (pid == -1)
			return (perror_return("fork", 1));
		if (!pid)
			child_process(current, fd, prev_fd, shell);
		else
			parent_process(current, fd, prev_fd);
		current = current->next;
	}
	while (waitpid(-1, &status, 0) > 0)
		;
	return (WEXITSTATUS(status));
}

int	execute_cmd(t_parser *parser, t_shell *shell)
{
	int	prev_fd;

	prev_fd = -1;
	if (prepare_heredocs(parser, shell))
	{
		shell->exit_status = 1;
		return (1);
	}
	// if (is_builtin(parser) && parser->next == NULL)
	// {
	// 	if (parser->redir)
	// 		exec_redir(parser->redir);
	// 	shell->exit_status = exec_builtin(parser. shell);
	// 	return (shell->exit_status);
	// }
	shell->exit_status = execute_pipeline(parser, &prev_fd, shell);
	if (prev_fd != -1)
		close (prev_fd);
	return (shell->exit_status);
}
