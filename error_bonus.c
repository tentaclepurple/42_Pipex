/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 18:16:14 by imontero          #+#    #+#             */
/*   Updated: 2023/09/07 15:20:33 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_error(char *str)
{
	ft_putstr_fd(str, 2);
	ft_putchar_fd('\n', 2);
	exit(-1);
}

void	ft_error_free_exit(char *s1, char *s2, t_px *px)
{

	ft_putstr_fd(s1, 2);
	ft_putstr_fd(s2, 2);
	free_mat(px->env_paths);
	free_fd(px);
	exit(-1);
}

void	free_mat(char **mat)
{
	int	i;

	i = 0;
	while (mat[i])
	{
		free(mat[i]);
		i++;
	}
	free(mat);
}

void	free_fd(t_px *px)
{
	int	i;

	i = 0;
	while (i < px->cmd_number - 1)
	{
		//fprintf(stderr, "freefd  i: %i. cmd num: %i", i, px->cmd_number);
		free(px->fd[i]);
		i++;
	}
	free(px->fd);
}

void	ft_close(t_px *px, int j)
{
	int	i;

	i = 0;

	while (i < j)
	{
		close(px->fd[i][0]);
		close(px->fd[i][1]);
		i++;
	}
}
