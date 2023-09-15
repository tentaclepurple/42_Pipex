/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_here_doc_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 12:32:53 by imontero          #+#    #+#             */
/*   Updated: 2023/09/15 19:31:04 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	write_here_doc_tmp(t_px *px)
{
	char	*line;
	char	*limit_n;

	px->fd_in = open(".tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	while (1)
	{
		line = getnextline(0);
		limit_n = ft_strjoin(px->limit, "\n");
		if (ft_strcmp(limit_n, line) == 0)
		{
			free(limit_n);
			break ;
		}
		free(limit_n);
		ft_putstr_fd(line, px->fd_in);
		free(line);
	}
	free(line);
	close(px->fd_in);
}

char	*getnextline(int fd)
{
	char	c;
	char	*str;
	char	*tmp;
	char	*aux;

	str = malloc(1 * sizeof(char));
	str[0] = 0;
	while (read(fd, &c, 1) > 0)
	{
		aux = str;
		tmp = malloc(2 * sizeof(char));
		tmp[0] = c;
		tmp[1] = 0;
		str = ft_strjoin(str, tmp);
		free(tmp);
		free(aux);
		if (c == '\n')
			break ;
	}
	return (str);
}
