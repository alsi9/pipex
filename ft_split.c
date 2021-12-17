/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ephantom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:11:14 by ephantom          #+#    #+#             */
/*   Updated: 2021/11/24 20:39:51 by ephantom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	count_word(char const *s, char c)
{
	unsigned int	n;
	unsigned int	i;

	n = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			n++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (n);
}

static int	count_char(char const *s, char c)
{
	unsigned int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char	**clear(char **dst)
{
	unsigned int	i;

	i = 0;
	while (dst[i])
		free(dst[i++]);
	free(dst);
	return (NULL);
}

static char	**write_split(char **dst, const char *s, char c)
{
	char			*word;
	unsigned int	j;

	j = 0;
	while (*s)
	{
		if (*s && *s == c)
			s++;
		else
		{
			word = (char *)malloc(sizeof(char) * (count_char(s, c) + 1));
			if (word == 0)
				return (clear(dst));
			while (*s && *s != c)
				word[j++] = *s++;
			word[j] = '\0';
			j = 0;
			*dst++ = word;
		}
	}
	*dst++ = 0;
	return (dst);
}

char	**ft_split(char const *s, char c)
{
	char			**dst;
	unsigned int	k;

	if (!s)
		return (0);
	k = count_word(s, c);
	dst = (char **)malloc(sizeof(char *) * (k + 1));
	if (dst == 0)
		return (0);
	if (write_split(dst, s, c))
		return (dst);
	return (NULL);
}
