/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmader <jmader@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:59:51 by jmader            #+#    #+#             */
/*   Updated: 2024/11/27 15:44:32 by jmader           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

char	*ft_free(char *buffer, char *buf)
{
	char	*temp;

	temp = ft_strjoin(buffer, buf);
	if (!temp)
	{
		free(buffer);
		return (NULL);
	}
	free(buffer);
	return (temp);
}

char	*ft_next_and_line(char **buffer, char **line)
{
	int		i;
	char	*next_buffer;

	i = 0;
	while ((*buffer)[i] && (*buffer)[i] != '\n')
		i++;
	*line = malloc(sizeof(char) * (i + 2));
	if (!*line)
		return (free(*buffer), NULL);
	i = 0;
	while ((*buffer)[i] && (*buffer)[i] != '\n')
	{
		(*line)[i] = (*buffer)[i];
		i++;
	}
	if ((*buffer)[i] == '\n')
		(*line)[i++] = '\n';
	(*line)[i] = '\0';
	next_buffer = NULL;
	if ((*buffer)[i])
		next_buffer = ft_strdup(*buffer + i);
	free(*buffer);
	return (next_buffer);
}

char	*read_and_append(int fd, char *res, char *buffer)
{
	int	byte_read;

	byte_read = 1;
	while (byte_read > 0)
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read < 0)
			return (NULL);
		buffer[byte_read] = '\0';
		res = ft_free(res, buffer);
		if (!res || ft_strchr(buffer, '\n'))
			break ;
	}
	return (res);
}

char	*read_file(int fd, char *res)
{
	char	*buffer;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	if (!res)
	{
		res = malloc(1);
		if (!res)
		{
			free(buffer);
			return (NULL);
		}
		res[0] = '\0';
	}
	res = read_and_append(fd, res, buffer);
	free(buffer);
	if (!res || res[0] == '\0')
	{
		free(res);
		return (NULL);
	}
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer = read_file(fd, buffer);
	if (!buffer)
		return (NULL);
	buffer = ft_next_and_line(&buffer, &line);
	return (line);
}
