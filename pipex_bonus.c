/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ephantom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 20:41:26 by ephantom          #+#    #+#             */
/*   Updated: 2021/11/30 20:10:10 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_execve(char *cmd, char **envp)
{
	char	**cmd2;
	char	*path_;

	if (!(*cmd))
		return ;
	cmd2 = ft_split(cmd, ' ');
	if (!cmd2[0])
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putstr_fd(cmd2[0], 2);
		write(2, "\n", 1);
		exit(127);
	}
	path_ = (path(cmd2, envp));
	if ((execve(path_, cmd2, envp)) == -1)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putstr_fd(cmd2[0], 2);
		write(2, "\n", 1);
		exit(127);
	}
	ft_free(cmd2);
}

static void	process_fork(char *cmd, char **envp)
{
	int	end[2];
	int	pid;

	if (pipe(end) == -1)
		ft_perror("pipex: error when creating the pipe: ");
	pid = fork();
	if (pid == -1)
		ft_perror("pipex: error when forking: ");
	if (pid == 0)
	{
		close(end[0]);
		if (dup2(end[1], STDOUT_FILENO) == -1)
			ft_perror("pipex: dup2 error: ");
		close(end[1]);
		ft_execve(cmd, envp);
	}
	else
	{
		close(end[1]);
		if (dup2(end[0], STDIN_FILENO) == -1)
			ft_perror("pipex: dup2 error: ");
		close(end[0]);
		waitpid(pid, NULL, 0);
	}
}

static void	pipex(int argc, char **argv, char **envp)
{
	int	count;
	int	fd_in;
	int	fd_out;

	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		count = 3;
		ft_here_doc(argc, argv);
		fd_out = ft_open_file(argv[argc - 1], 2);
	}
	else
	{
		count = 2;
		fd_in = ft_open_file(argv[1], 0);
		fd_out = ft_open_file(argv[argc - 1], 1);
		if (dup2(fd_in, STDIN_FILENO) == -1)
			ft_perror("pipex: dup2(fd_in) error: ");
	}
	while (count < argc - 2)
		process_fork(argv[count++], envp);
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		ft_perror("pipex: dup2(fd_out) error: ");
	ft_execve(argv[argc - 2], envp);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc < 5)
	{
		ft_putstr_fd("pipex: error: wrong count of arguments\n", 2);
		return (1);
	}
	pipex(argc, argv, envp);
	return (0);
}
