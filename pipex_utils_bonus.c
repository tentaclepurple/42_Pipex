/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 18:56:30 by imontero          #+#    #+#             */
/*   Updated: 2023/09/08 11:24:14 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
/* 
	Return 1 for here_doc and 0 for pipex
*/
int	check_here_doc(int argc, char **argv, t_px *px)
{
	int	i;

	i = 0;
	while (i < argc - 1)
	{
		if (argv[i] == 0)
			ft_error("Empty argument");
		i++;
	}
	if (!ft_strcmp(argv[1], "here_doc") && argc > 5
		&& check_files(argv[argc -1], 'w'))
	{
		px->flag_here_doc = 1;
		ft_strcpy(px->limit, argv[2]);
		return (0);
	}
	else if (px->flag_here_doc == 0 && argc > 4 && check_files(argv[1], 'r')
		&& checkfiles(argv[argc - 1], 'w'))
	{
		return (1);
	}
}

/*
	check if the file can be
	read (receive 'r')
	or written ('w')
	returns 1 if ok
*/
int	check_files(char *file, char c)
{
	if (c == 'r')
	{
		if (access(file, R_OK) == 0)
			return (1);
	}
	else if (c == 'w')
	{
		if (access(file, W_OK) == 0)
			return (1);
	}
	return (0);
}

void	get_env_path(char **env, t_px *px)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5))
			px->env_paths = ft_split(env[i] + 5, ':');
		i++;
	}
}

void	ft_execve(t_px *px, char *argv, char **env)
{
	int		i;
	char	**arg_cmd_and_flags;
	char	*path_and_cmd;

	i = 0;
	arg_cmd_and_flags = ft_split(argv, ' ');
	while (px->env_paths[i])
	{
		path_and_cmd = ft_strjoin(px->env_paths[i], "/");
		path_and_cmd = ft_strjoin(path_and_cmd, arg_cmd_and_flags[0]);

		if (!access(path_and_cmd, F_OK))
			execve(path_and_cmd, arg_cmd_and_flags, env);
		i++;
	}
	free_mat(arg_cmd_and_flags);
	free_mat(px->env_paths);
	free(path_and_cmd);
	ft_error_free_exit("Command not found: ", argv, px);
}

void	ft_alloc_fd(t_px *px)
{
	int	i;

	i = 0;
	px->fd = malloc(sizeof(int *) * (px->cmd_number - 1));
	while (i < px->cmd_number - 1)
	{
		px->fd[i] = malloc(sizeof(int) * 2);
		pipe(px->fd[i]);
		i++;
	}
}
