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

void	child(char **argv, int *p_fd, char **envp)
{
	int	infile;

	infile = open(argv[1], O_RDONLY);
	if (infile == -1)
		ft_error(argv[1], 1);
	dup2(infile, STDIN_FILENO);
	dup2(p_fd[1], STDOUT_FILENO);
	close(infile);
	close(p_fd[0]);
	close(p_fd[1]);
	execute(argv[2], envp);
}

void	parent(char **argv, int *p_fd, char **envp)
{
	int	outfile;

	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile == -1)
		ft_error(argv[4], 1);
	dup2(p_fd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	close(p_fd[0]);
	close(p_fd[1]);
	execute(argv[3], envp);
}

void	wait_children(pid_t pid1, pid_t pid2)
{
	int	status;

	waitpid(pid1, NULL, 0);
	waitpid(pid2, &status, 0);
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
}

int	execute_cmd(t_parser *parser)
{
	int			fd[2];
	pid_t		pid1;

	if (pipe(fd) == -1)
		return (1);
	while (parser->next)
	{
		pid1 = fork();
		if (pid1 == -1)
			return(1);
		if (!pid1)
			child();
		parser = parser->next;
	}
	pid2 = fork();
	if (pid2 == -1)
		return(1);
	if (!pid2)
		parent(argv, fd, envp);
	close(fd[0]);
	close(fd[1]);
	wait_children(pid1, pid2);
	return (0);
}