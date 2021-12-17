/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ephantom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 11:20:34 by ephantom          #+#    #+#             */
/*   Updated: 2021/11/30 18:53:35 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_open_file(char *str, int i)
{
	int	fd;

	fd = -1;
	if (i == 0)
		fd = open(str, O_RDONLY);
	else if (i == 1)
		fd = open(str, O_RDWR | O_CREAT | O_TRUNC, 0777);
	else if (i == 2)
		fd = open(str, O_RDWR | O_CREAT | O_APPEND, 0777);
	if (fd == -1)
		ft_perror("pipex: open error");
	return (fd);
}
