/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ephantom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 11:21:49 by ephantom          #+#    #+#             */
/*   Updated: 2021/12/01 10:22:14 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	write_heredoc(int *end, char *stop)
{
	char	*line;

	line = NULL;
	close(end[0]);
	ft_putstr_fd("pipe heredoc> ", 1);
	while (get_next_line(&line))
	{
		if ((ft_strncmp(stop, line, ft_strlen(stop))) == 0)
		{
			free(line);
			close(end[1]);
			exit(0);
		}
		ft_putstr_fd("pipe heredoc> ", 1);
		if (write(end[1], line, ft_strlen(line)) == -1)
			ft_perror("pipex: write error: ");
		free(line);
		line = NULL;
	}
	free(line);
	line = NULL;
	close(end[1]);
	ft_perror("pipex: write here_doc error: ");
}

void	ft_here_doc(int argc, char **argv)
{
	int	end[2];
	int	pid;

	if (argc < 6)
		ft_putstr_fd("pipex: error: wrong count of arguments\n", 2);
	if (pipe(end) == -1)
		ft_perror("pipex: error when creating the pipe: ");
	pid = fork();
	if (pid == -1)
		ft_perror("pipex: error when forking: ");
	if (pid == 0)
		write_heredoc(end, argv[2]);
	else
	{
		close(end[1]);
		if (dup2(end[0], STDIN_FILENO) == -1)
			ft_perror("pipex: dup2 error: ");
		close(end[0]);
		waitpid(pid, NULL, 0);
	}
}
