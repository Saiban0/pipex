/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 17:45:48 by bchedru           #+#    #+#             */
/*   Updated: 2024/01/22 15:30:42 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include "libft/libft.h"

int		open_file(char *file, int n);
char	*ft_getenv(char *name, char **env);
char	*ft_getpath(char *cmd, char **env);
void	exec(char *cmd, char **env);
void	ft_free_tab(char **tab);
int		check_dir(char *cmd);
void	exit_handler(int n_exit);

#endif