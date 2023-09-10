/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 08:40:30 by imontero          #+#    #+#             */
/*   Updated: 2023/09/08 11:21:13 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "my_libft/libft/libft.h"
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>

typedef struct s_px
{
	char	**env_paths;
	int		fd[2];
	int		fd_in;
	int		fd_out;
}	t_px;

void	pipex(t_px *px, char **argv, char **env);
void	first_child_cmd(t_px *px, char **argv, char **env);
void	last_child_cmd(t_px *px, char **argv, char **env);
void	get_env_path(char **env, t_px *px);
void	ft_execve(t_px *px, char *argv, char **env);
void	check_files(int argc, char **argv);
void	ft_error(char *str);
void	free_mat(char **mat);
void	ft_error_free_exit(char *str, t_px *px);

#endif