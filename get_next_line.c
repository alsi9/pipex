/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ephantom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 11:28:47 by ephantom          #+#    #+#             */
/*   Updated: 2021/12/21 18:00:41 by ephantom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int        get_next_line(char **line)
{
    int        bytes_buf;
    char    buffer[1];
    int        i;
    char    *join;

    if (!(*line = malloc(1)) || !line)
        return (-1);
    (*line)[0] = '\0';
    while ((bytes_buf = read(0, buffer, 1)) > 0)
    {
        if (buffer[0] == '\0' || buffer[0] == '\n')
            break ;
        i = 0;
        while ((*line)[i])
            i++;
        if (!(join = malloc(i + 2)))
            return (-1);
        i = 0;
        while ((*line)[i] != '\0')
        {
            join[i] = (*line)[i];
            i++;
        }
        join[i++] = buffer[0];
        join[i++] = '\0';
        free(*line);
        *line = join;
    }
    return (bytes_buf);
}
