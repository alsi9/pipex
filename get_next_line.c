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
    int     i;
    char    buffer[1];
    int     num;
    char    *join;

    
    i = 0;
    (*line) = (char *)malloc(sizeof(char) * 1);
    if (!(*line) || !line)
        return (-1);
    (*line)[0] = '\0';
    num = 1;
    while ((num = read(0, buffer, 1)) > 0)
    {
        if (buffer[0] == '\0' || buffer[0] == '\n')
            break ;
        i = 0;
        while ((*line)[i])
            i++;
        join = (char *)malloc(sizeof(char) * (i + 2));
        if (!join)
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
    return (num);
}
