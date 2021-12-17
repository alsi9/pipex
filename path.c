/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ephantom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 20:42:48 by ephantom          #+#    #+#             */
/*   Updated: 2021/11/30 21:30:52 by ephantom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**get_path(char **envp)
{
	int		i;
	char	**path;

	i = 0;
	path = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = ft_split(envp[i] + 5, ':');
			break ;
		}
		i++;
	}
	if (!path)
	{
		perror("pipex: unexpected error: ");
		exit(1);
	}
	return (path);
}

char	*path(char **cmd, char **envp)
{
	char	*find_dir;
	char	*find_command;
	int		j;
	char	**path;

	j = 0;
	path = get_path(envp);
	while (path[j])
	{
		if (cmd[0][0] != '/')
		{
			find_dir = ft_strjoin(path[j], "/");
			find_command = ft_strjoin(find_dir, cmd[0]);
			free(find_dir);
		}
		else
			find_command = cmd[0];
		if (!(access(find_command, F_OK)))
			return (find_command);
		if (cmd[0][0] != '/')
			free(find_command);
		j++;
	}
	ft_free(path);
	return (NULL);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*dest;
	size_t	i;
	size_t	j;

	i = ft_strlen(s1);
	j = ft_strlen(s2);
	if (!s1 || !s2)
		return (0);
	dest = (char *)malloc(sizeof(char) * (i + j + 1));
	if (!dest)
		return (0);
	i = 0;
	j = 0;
	while (s1[i])
		dest[j++] = s1[i++];
	i = 0;
	while (s2[i])
		dest[j++] = s2[i++];
	dest[j] = '\0';
	return (dest);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if ((((unsigned char *)s1)[i] == ((unsigned char *)s2)[i])
			&& ((unsigned char *)s1)[i])
			i++;
		else
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
	}
	return (0);
}
