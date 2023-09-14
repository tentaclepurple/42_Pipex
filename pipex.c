/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:39:27 by imontero          #+#    #+#             */
/*   Updated: 2023/09/12 12:59:09 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_child_cmd_st(t_px *px, char **argv, char **env)
{
	get_env_path_st(env, px);
	px->fd_in = open(argv[1], O_RDONLY);
	if (px->fd_in < 0)
		ft_error_free_exit_st("Error opening infile", px);
	if (dup2(px->fd[1], STDOUT_FILENO) < 0)
		ft_error_free_exit_st("dup error", px);
	if (dup2(px->fd_in, STDIN_FILENO) < 0)
		ft_error_free_exit_st("dup error", px);
	close(px->fd_in);
	close(px->fd[0]);
	close(px->fd[1]);
	ft_execve_st(px, argv[2], env);
}

void	last_child_cmd_st(t_px *px, char **argv, char **env)
{
	get_env_path_st(env, px);
	px->fd_out = open(argv[4], O_CREAT | O_TRUNC | O_WRONLY, 0777);
	if (px->fd_out < 0)
		ft_error_free_exit_st("Error opening outfile", px);
	if (dup2(px->fd[0], STDIN_FILENO) < 0)
		ft_error_free_exit_st("dup error", px);
	if (dup2(px->fd_out, STDOUT_FILENO) < 0)
		ft_error_free_exit_st("dup error", px);
	close(px->fd[0]);
	close(px->fd_out);
	close(px->fd[1]);
	ft_execve_st(px, argv[3], env);
}

void	pipex_st(t_px *px, char **argv, char **env)
{
	pid_t	pid;

	pipe(px->fd);
	pid = fork();
	if (pid == 0)
		first_child_cmd_st(px, argv, env);
	else if (pid < 0)
		ft_error_free_exit_st("Error creating child", px);
	wait(NULL);
	pid = fork();
	if (pid == 0)
		last_child_cmd_st(px, argv, env);
	else if (pid < 0)
		ft_error_free_exit_st("Error creating child", px);
	close(px->fd[0]);
	close(px->fd[1]);
	wait(NULL);
}

int	main(int argc, char **argv, char **env)
{
	t_px	px;

	if (argc != 5)
		ft_error_st("Invalid argument number");
	check_files_st(argc, argv);
	ft_bzero(&px, sizeof(struct s_px));
	pipex_st(&px, argv, env);
	return (0);
}
