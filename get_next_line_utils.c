/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaly <omaly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 12:20:57 by omaly             #+#    #+#             */
/*   Updated: 2025/07/12 19:33:17 by omaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

char	*ft_strchr(const char *s, char c)
{
	if (!s)
	{
		return (NULL);
	}
	while (s && *s != '\0')
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

size_t	ft_strlen(char const *s)
{
	size_t	len;

	len = 0;
	while (s && s[len] != '\0')
	{
		len++;
	}
	return (len);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*join;
	size_t	pos;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	join = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!join)
		return (NULL);
	pos = 0;
	while (pos < s1_len)
	{
		join[pos] = s1[pos];
		pos++;
	}
	pos = 0;
	while (pos < s2_len)
	{
		join[s1_len + pos] = s2[pos];
		pos++;
	}
	join[s1_len + pos] = '\0';
	return (join);
}

char	*ft_strndup(char const *s, size_t n)
{
	char	*dup;
	size_t	i;

	dup = malloc(n + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (s[i] != '\0' && i < n)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
