/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:24:36 by bchedru           #+#    #+#             */
/*   Updated: 2024/01/30 15:29:46 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_file(char *file, int in_or_out)
{
	int	ret;

	if (in_or_out == 0)
		ret = open(file, O_RDONLY, 0777);
	if (in_or_out == 1)
		ret = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (ret == -1)
	{
		ft_putstr_fd("pipex: file not found: ", 2);
		ft_putendl_fd(file, 2);
	}
	return (ret);
}

void	ft_free_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	*ft_getenv(char *name, char **envp)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		sub = ft_substr(envp[i], 0, j);
		if (ft_strcmp(sub, name) == 0)
		{
			free(sub);
			return (envp[i] + j + 1);
		}
		free(sub);
		i++;
	}
	return (".");
}

int	check_dir(char *cmd)
{
	int	fd;

	fd = open(cmd, __O_DIRECTORY);
	if (fd != -1)
	{
		close(fd);
		return (-1);
	}
	if (errno == ENOTDIR)
		return (1);
	return (0);
}

char	*ft_getpath(char *cmd, char **envp)
{
	int		i;
	char	*exec;
	char	**allpath;
	char	*temp_path;
	char	**curr_cmd;

	i = -1;
	allpath = ft_split(ft_getenv("PATH", envp), ':');
	curr_cmd = ft_split(cmd, ' ');
	while (allpath[++i])
	{
		temp_path = ft_strjoin(allpath[i], "/");
		exec = ft_strjoin(temp_path, curr_cmd[0]);
		free(temp_path);
		if (access(exec, F_OK | X_OK) == 0 && check_dir(exec))
		{
			ft_free_tab(curr_cmd);
			return (exec);
		}
		free(exec);
	}
	ft_free_tab(allpath);
	ft_free_tab(curr_cmd);
	return (cmd);
}
