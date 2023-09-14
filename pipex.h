/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 08:40:30 by imontero          #+#    #+#             */
/*   Updated: 2023/09/14 13:44:40 by imontero         ###   ########.fr       */
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
	int		flag_path_found;
}	t_px;

void	pipex_st(t_px *px, char **argv, char **env);
void	first_child_cmd_st(t_px *px, char **argv, char **env);
void	last_child_cmd_st(t_px *px, char **argv, char **env);
void	get_env_path_st(char **env, t_px *px);
void	ft_execve_st(t_px *px, char *argv, char **env);
void	check_files_st(int argc, char **argv);
void	ft_error_st(char *str);
void	free_mat_st(char **mat);
void	ft_error_free_exit_st(char *str, t_px *px);

#endif