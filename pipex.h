/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ephantom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 21:33:57 by ephantom          #+#    #+#             */
/*   Updated: 2021/11/30 21:34:03 by ephantom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>
# include <stdio.h>

char	**ft_split(char const *s, char c);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_putstr_fd(char *s1, int fd);
size_t	ft_strlen(const char *str);
char	*path(char **cmd, char **envp);
int		get_next_line(char **line);
void	ft_here_doc(int argc, char **argv);
int		main(int argc, char **argv, char **envp);
void	ft_perror(char *str);
void	ft_free(char **str);
int		ft_open_file(char *str, int i);

#endif
