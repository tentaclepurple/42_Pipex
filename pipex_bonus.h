/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 08:40:30 by imontero          #+#    #+#             */
/*   Updated: 2023/09/08 12:30:19 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "my_libft/libft/libft.h"
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>

typedef struct s_px
{
	char	**env_paths;
	int		**fd;
	int		fd_in;
	int		fd_out;
	int		argccpy;
	int		cmd_number;
	int		flag_here_doc;
	char	*limit;
}	t_px;

void	pipex(t_px *px, char **argv, char **env);
void	first_child_cmd(t_px *px, char **argv, char **env);
void	last_child_cmd(int i, t_px *px, char **argv, char **env);
void	core_child_cmd(int i, t_px *px, char **argv, char **env);
void	get_env_path(char **env, t_px *px);
void	ft_execve(t_px *px, char *argv, char **env);
int		check_files(char *file, char c);
int		check_here_doc(int argc, char **argv, t_px *px);
void	ft_error(char *str);
void	free_mat(char **mat);
void	free_fd(t_px *px);
void	ft_error_free_exit(char *s1, char *s2, t_px *px);
void	ft_alloc_fd(t_px *px);
void	ft_close(t_px *px, int j);


#endif