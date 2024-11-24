/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbmader <jbmader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:59:51 by jmader            #+#    #+#             */
/*   Updated: 2024/11/22 20:11:34 by jbmader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t				i;
	const unsigned char	*s;
	unsigned char		*d;

	s = (const unsigned char *)src;
	d = (unsigned char *)dest;
	if (d == s)
		return (dest);
	if (s < d && d < s + n)
	{
		while (n-- > 0)
			d[n] = s[n];
	}
	else
	{
		i = 0;
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dest);
}

int	build_line(char **line, char *buf)
{
	int		i;
	char	*tmp;
	char	*substr;

	i = 0;
	tmp = *line;
	while (buf[i] != '\0')
	{
		if (buf[i] == '\n')
		{
			substr = ft_substr(buf, 0, i);
			*line = ft_strjoin(*line, substr);
			free(substr);
			free(tmp);
			ft_memmove(buf, buf + i + 1, BUFFER_SIZE - i);
			return (1);
		}
		i++;
	}
	substr = ft_substr(buf, 0, i);
	*line = ft_strjoin(*line, substr);
	free(substr);
	free(tmp);
	buf[0] = '\0';
	return (0);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*line;
	int			nb_read;

	line = malloc(1);
	if (!line)
		return (NULL);
	line[0] = '\0';
	nb_read = 1;
	while (nb_read > 0)
	{
		if (buf[0] == '\0')
		{
			nb_read = read(fd, buf, BUFFER_SIZE);
			if (nb_read == -1)
			{
				free(line);
				return (NULL);
			}
			buf[nb_read] = '\0';
		}
		if (nb_read > 0)
			buf[nb_read] = '\0';
		if (build_line(&line, buf) == 1)
			return (line);
	}
	if (line[0] != '\0')
		return (line);
	free(line);
	return (NULL);
}
