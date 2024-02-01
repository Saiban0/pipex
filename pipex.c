/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:06:02 by bchedru           #+#    #+#             */
/*   Updated: 2024/01/30 14:45:40 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec(char *cmd, char **envp)
{
	char	**s_cmd;
	char	*path;

	if (cmd[0] == '\0')
		exit(0);
	s_cmd = ft_split(cmd, ' ');
	path = ft_getpath(s_cmd[0], envp);
	if (execve(path, s_cmd, envp) == -1)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(s_cmd[0], 2);
		ft_free_tab(s_cmd);
		exit(0);
	}
}

void	child(char **av, int *p_fd, char **envp)
{
	int		fd;

	fd = open_file(av[1], 0);
	dup2(fd, 0);
	dup2(p_fd[1], 1);
	close(p_fd[0]);
	exec(av[2], envp);
}

void	parent(char **av, int *p_fd, char **envp)
{
	int		fd;
	int		status;

	waitpid(-1, &status, 0);
	fd = open_file(av[4], 1);
	dup2(fd, 1);
	dup2(p_fd[0], 0);
	close(p_fd[1]);
	exec(av[3], envp);
}

void	exit_handler(int n_exit)
{
	if (n_exit == 1)
		ft_putstr_fd("Syntax error : ./pipex infile cmd cmd outfile\n", 2);
	else if (n_exit == 2)
		ft_putstr_fd("File not found\n", 2);
	exit(0);
}

int	main(int ac, char **av, char **envp)
{
	int		p_fd[2];
	pid_t	pid;

	if (ac != 5)
		exit_handler(1);
	if (pipe(p_fd) == -1)
		exit(-1);
	pid = fork();
	if (pid == -1)
		exit(-1);
	if (!pid)
		child(av, p_fd, envp);
	parent(av, p_fd, envp);
}
