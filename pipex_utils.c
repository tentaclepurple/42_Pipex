/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 18:56:30 by imontero          #+#    #+#             */
/*   Updated: 2023/09/14 13:53:19 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_files_st(int argc, char **argv)
{
	int	in;
	int	out;

	in = open(argv[1], O_RDONLY);
	out = open(argv[argc - 1], O_RDONLY);
	if (in < 0 || out < 0)
		ft_error_st("Invalid in/out files");
	close(in);
	close(out);
}

void	get_env_path_st(char **env, t_px *px)
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

void	ft_execve_st(t_px *px, char *argv, char **env)
{
	int		i;
	char	**arg_cmd_and_flags;
	char	*path_and_cmd;
	char	*aux;

	i = 0;
	arg_cmd_and_flags = ft_split(argv, ' ');
	while (px->env_paths[i])
	{
		aux = ft_strjoin(px->env_paths[i++], "/");
		path_and_cmd = ft_strjoin(aux, arg_cmd_and_flags[0]);
		free(aux);
		if (!access(path_and_cmd, F_OK))
		{
			px->flag_path_found = 1;
			break ;
		}
		else
			free(path_and_cmd);
	}
	if (px->flag_path_found == 1)
		execve(path_and_cmd, arg_cmd_and_flags, env);
	free_mat_st(arg_cmd_and_flags);
	ft_error_free_exit_st("Command not found", px);
}
