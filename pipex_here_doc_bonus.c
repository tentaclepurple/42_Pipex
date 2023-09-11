/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_here_doc_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 12:32:53 by imontero          #+#    #+#             */
/*   Updated: 2023/09/11 20:04:52 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	write_here_doc_tmp(t_px *px)
{
	char	*line;

	px->fd_in = open(".tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	while(1)
	{
		line = get_next_line(0);
		if (ft_strncmp(px->limit, line, ft_strlen(line)-1) == 0)
		{
			break;
		}
		ft_putstr_fd(line, px->fd_in);
		free(line);	
	}
	free(line);
	close(px->fd_in);
}