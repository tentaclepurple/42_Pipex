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

#include "pipex.h"

void	ft_error(char *str)
{
	ft_printf("%s\n", str);
	exit(-1);
}

void	ft_error_free_exit(char *str, t_px *px)
{
	free_mat(px->env_paths);
	ft_printf("%s\n", str);
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
