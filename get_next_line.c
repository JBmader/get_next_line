/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbmader <jbmader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:59:51 by jmader            #+#    #+#             */
/*   Updated: 2024/11/22 19:12:36 by jbmader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

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
			return (1);
		}
		i++;
	}
	substr = ft_substr(buf, 0, i);
	*line = ft_strjoin(*line, substr);
	free(substr);
	free(tmp);
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
	nb_read = -1;
	while (nb_read != 0)
	{
		nb_read = read(fd, buf, BUFFER_SIZE);
		if (nb_read == -1)
		{
			free(line);
			return (NULL);
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
