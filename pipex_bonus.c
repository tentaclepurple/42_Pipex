/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:39:27 by imontero          #+#    #+#             */
/*   Updated: 2023/09/08 13:35:22 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	first_child_cmd(t_px *px, char **argv, char **env)
{
	get_env_path(env, px);
	px->fd_in = open(argv[1], O_RDONLY);
	if (dup2(px->fd[0][1], STDOUT_FILENO) < 0)
		ft_error_free_exit("dup error", NULL, px);
	if (dup2(px->fd_in, STDIN_FILENO) < 0)
		ft_error_free_exit("dup error", NULL, px);
	close(px->fd_in);
	ft_close(px, px->cmd_number - 1);
	ft_execve(px, argv[2], env);
}

void	core_child_cmd(int i, t_px *px, char **argv, char **env)
{
	get_env_path(env, px);
	if (dup2(px->fd[i - 1][0], STDIN_FILENO) < 0)
		ft_error_free_exit("dup error", NULL, px);
	if (dup2(px->fd[i][1], STDOUT_FILENO) < 0)
		ft_error_free_exit("dup error", NULL, px);
	ft_close(px, px->cmd_number - 1);
	ft_execve(px, argv[i + 2], env);
}

void	last_child_cmd(int i, t_px *px, char **argv, char **env)
{
	get_env_path(env, px);
	px->fd_out = open(argv[px->argccpy - 1], O_TRUNC | O_WRONLY, 0777);
	if (dup2(px->fd[i - 1][0], STDIN_FILENO) < 0)
		ft_error_free_exit("dup error", NULL, px);
	if (dup2(px->fd_out, STDOUT_FILENO) < 0)
		ft_error_free_exit("dup error", NULL, px);
	close(px->fd_out);
	ft_close(px, i);
	ft_execve(px, argv[px->argccpy - 2], env);
}

void	pipex(t_px *px, char **argv, char **env)
{
	pid_t	pid;
	int		i;

	i = 0;
	while (i + 2 < px->argccpy - 1)
	{
		pid = fork();
		if (pid == 0)
		{
			if (i == 0)
				first_child_cmd(px, argv, env);
			else if (i + 2 == px->argccpy - 2)
				last_child_cmd(i, px, argv, env);
			else
				core_child_cmd(i, px, argv, env);
		}
		ft_close(px, i);
		waitpid(pid, NULL, 0);
		i++;
	}
	free_fd(px);
}

int	main(int argc, char **argv, char **env)
{
	t_px	px;

	ft_bzero(&px, sizeof(struct s_px));
	if (argc < 5)
		ft_error("Invalid argument number");
	
	
	
	check_files(argc, argv);
	px.argccpy = argc;
	px.cmd_number = argc - 3;
	ft_alloc_fd(&px);
	pipex(&px, argv, env);
	return (0);
}
