/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parden <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 12:39:12 by parden            #+#    #+#             */
/*   Updated: 2024/06/07 13:20:02 by parden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
# define BUFFER_SIZE 1024

size_t	append_line(char *line, char *buf, size_t cap)
{
	size_t	i;

	i = 0;
	while (i < cap)
	{
		line[i] = buf[i];
		i++;
		if (buf[i - 1] == '\n')
			return (i);
	}
	return (0);
}

void	my_realloc(char **line, size_t *line_size, size_t bytes_total)
{
	char *res;

	res = malloc(*line_size * 2);
	memcpy(res, *line, bytes_total);
	free(*line);
	*line_size *= 2;
	*line = res;
}


char	*get_next_line(int fd)
{
	char		buf[BUFFER_SIZE];
	size_t		bytes_read;
	size_t		nl_start;
	char		*line;
	static char	extra[BUFFER_SIZE];

	append(line, extra, strlen(extra));
	nl_start = 0;
	bytes_read = BUFFER_SIZE;
	while (!nl_start && bytes_read == BUFFER_SIZE)
	{
		if (line_size < bytes_total + BUFFER_SIZE)
			my_realloc(&line, &line_size);
		bytes_read = read(fd, buf, BUFFER_SIZE);
		nl_start = append_line(line, buf, BUFFER_SIZE);
		bytes_total += BUFFER_SIZE;
	}
	if (bytes_read == BUFFER_SIZE)
	{
		memcpy(extra, buf + nl_start, BUFFER_SIZE - nl_start);
		extra[BUFFER_SIZE - nl_start] = 0;
	}
	else
		extra[0] = 0;
	return (line);
}
