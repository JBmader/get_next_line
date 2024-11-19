/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmader <jmader@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:59:51 by jmader            #+#    #+#             */
/*   Updated: 2024/11/19 15:13:27 by jmader           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char			*buf[BUFFER_SIZE + 1];
	char			*line;
	static int		nb_read;
	int				count;

	nb_read = -1;
	count = 0;
	if (nb_read != 0)
	{
		nb_read = read(fd, buf, BUFFER_SIZE);
		if (nb_read == -1)
		{
			printf("Read error!\n");
			return (1);
		}
		buf[nb_read] = '\0';
		// Print the buffer contents after read
		printf("\e[36m%d : [\e[0m%s\e[36m]\e[0m\n", count, buf);
		count++;
	}
}
