/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaly <omaly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 12:21:09 by omaly             #+#    #+#             */
/*   Updated: 2025/07/12 19:30:58 by omaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char	*ft_strchr(const char *s, char c);
size_t	ft_strlen(char const *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strndup(char const *s, size_t n);

char	*read_and_stash(int fd, char *stash)
{
	char	*buffer;
	char	*tmp;
	ssize_t	bytes_read;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (free(stash), NULL);
	bytes_read = 1;
	while (0 < bytes_read && ft_strchr(stash, '\n') == NULL)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(buffer), free(stash), NULL);
		if (bytes_read == 0)
			return (free(buffer), stash);
		buffer[bytes_read] = '\0';
		tmp = ft_strjoin(stash, buffer);
		free(stash);
		if (tmp == NULL)
			return (free(buffer), NULL);
		stash = tmp;
	}
	free(buffer);
	return (stash);
}

char	*extract_line(char *stash)
{
	size_t	len;

	if (!stash || stash[0] == '\0')
		return (NULL);
	len = 0;
	while (stash[len] && stash[len] != '\n')
		len++;
	if (stash[len] == '\n')
		len++;
	return (ft_strndup(stash, len));
}

char	*clean_stash(char *stash)
{
	char	*newl;
	char	*clean;

	if (!stash)
		return (NULL);
	newl = ft_strchr(stash, '\n');
	if (!newl)
		return (free(stash), NULL);
	newl++;
	if (*newl == '\0')
		return (free(stash), NULL);
	clean = ft_strndup(newl, ft_strlen(newl));
	free(stash);
	return (clean);
}

char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_and_stash(fd, stash);
	if (stash == NULL)
		return (NULL);
	line = extract_line(stash);
	if (line == NULL)
	{
		if (stash && stash[0] != '\0')
			line = ft_strndup(stash, ft_strlen(stash));
		free(stash);
		stash = NULL;
		return (line);
	}
	stash = clean_stash(stash);
	return (line);
}
