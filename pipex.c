/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ephantom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 20:41:26 by ephantom          #+#    #+#             */
/*   Updated: 2021/11/30 19:37:44 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	child_process_1(int *end, char **argv, char **envp)
{
	int		infile;
	char	**cmd1;

	infile = open(argv[1], O_RDONLY);
	if (infile < 0)
	{
		write(2, "pipex: ", 7);
		ft_perror(argv[1]);
	}
	close(end[0]);
	dup2(end[1], STDOUT_FILENO);
	close(end[1]);
	dup2(infile, STDIN_FILENO);
	cmd1 = ft_split(argv[2], ' ');
	if (execve((path(cmd1, envp)), cmd1, envp) == -1)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putstr_fd(argv[2], 2);
		ft_putstr_fd("\n", 2);
		exit(127);
	}
}

static void	child_process_2(int *end, char **argv, char **envp)
{
	int		outfile;
	char	**cmd2;

	outfile = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (outfile < 0)
	{
		write(2, "pipex: ", 7);
		ft_perror(argv[4]);
	}
	close(end[1]);
	dup2(end[0], STDIN_FILENO);
	close(end[0]);
	dup2(outfile, STDOUT_FILENO);
	cmd2 = ft_split(argv[3], ' ');
	if (execve((path(cmd2, envp)), cmd2, envp) == -1)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putstr_fd(argv[3], 2);
		ft_putstr_fd("\n", 2);
		exit(127);
	}
}

static void	process_fork(int *end, char **argv, char **envp)
{
	int	child_1;
	int	child_2;

	child_1 = fork();
	if (child_1 == -1)
		ft_perror("pipex: error when forking: ");
	if (child_1 == 0)
		child_process_1(end, argv, envp);
	child_2 = fork();
	if (child_2 == -1)
		ft_perror("pipex: error when forking: ");
	if (child_2 == 0)
		child_process_2(end, argv, envp);
}

int	main(int argc, char **argv, char **envp)
{
	int		status;
	int		end[2];

	if (argc != 5)
	{
		ft_putstr_fd("pipex: inter: ./pipex infile cmd1 cmd2 outfile\n", 2);
		return (1);
	}
	if (pipe(end) == -1)
	{
		perror("pipex: error when creating the pipe: ");
		return (1);
	}
	process_fork(end, argv, envp);
	close(end[0]);
	close(end[1]);
	waitpid(-1, &status, 0);
	return (0);
}
