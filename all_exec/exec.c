#include "../minishell.h"

void	execute(char *cmd_str, char **envp)
{
	char	**cmd;
	char	*path;

	if (!cmd_str || !cmd_str[0])
		exit(127);
	cmd = ft_split(cmd_str, ' ');
	if (!cmd || !cmd[0])
		exit(127);
	path = get_path(cmd[0], envp);
	if (!path)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(cmd[0], 2);
		free_tab(cmd);
		exit(127);
	}
	execve(path, cmd, envp);
	perror(cmd[0]);
	free(path);
	free_tab(cmd);
	exit(126);
}

int	child_process(t_parser *current, int fd, int *prev_fd, char **envp)
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
	execve(current->arg[0], current->arg, envp);
	return (1);
}

void	parent(t_parser *current, int fd, int *prev_fd, char **envp)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (current->next)
	{
		close(fd[1]);
		*prev_fd = fd[0];
	}
}

int	execute_cmd(t_parser *parser, char **envp)
{
	int			fd[2];
	int			prev_fd;
	pid_t		pid;
	t_parser	*current;

	prev_fd = -1;
	current = parser;
	while (current)
	{
		if (current->next)
		{
			if (pipe(fd) == -1)
				return (1);
		}
		pid = fork();
		if (pid == -1)
			return(1);
		if (!pid)
		{
			if (child_process(current, fd, &prev_fd, envp) == 1)
				return (1);
		}
		else
			parent_process(current, fd, &prev_fd, envp);
		current = current->next;
	}
	while (wait(NULL) > 0)
		;
	return (0);
}