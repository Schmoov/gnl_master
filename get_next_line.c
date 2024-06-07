/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parden <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 12:39:12 by parden            #+#    #+#             */
/*   Updated: 2024/06/07 19:40:01 by parden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
# define BUFFER_SIZE 1024
# define FD_MAX 1024

size_t	append_line(char *line, char *buf, size_t cap)
{
	size_t	i;

	i = 0;
	while (i < cap)
	{
		line[i] = buf[i];
		i++;
		if (buf[i - 1] == '\n')
			break;
	}
	return (i);
}

void	my_realloc(char **line, size_t *size_line, size_t len_line)
{
	char *res;

	res = malloc(*size_line * 2);
	memcpy(res, *line, len_line);
	free(*line);
	*size_line *= 2;
	*line = res;
}

void	save_extra(char *extra, char *buf, size_t bytes_read)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < bytes_read && buf[i] != '\n')
		i++;
	i++;
	while (i < bytes_read)
	{
		extra[j] = buf[i];
		i++;
		j++;
	}
	while (j < BUFFER_SIZE)
	{
		extra[j] = 0;
		j++;
	}
}

void	get_line_from_fd(char *line, size_t *len_line, char *extra, int fd)
{
	char	buf[BUFFER_SIZE];
	int		bytes_read;
	size_t	size_line;

	bytes_read = BUFFER_SIZE;
	size_line = 2 * BUFFER_SIZE + 1;

	while (line[*len_line - 1] != '\n' && bytes_read)
	{
		if (*len_line + BUFFER_SIZE > size_line)
			my_realloc(&line, &size_line, *len_line);
		bytes_read = read(fd, buf, BUFFER_SIZE);
		//TODO what if bytes read == -1 ?
		*len_line += append_line(line + *len_line, buf, bytes_read);
	}
	save_extra(extra, buf, bytes_read);
}

char	*get_next_line(int fd)
{
	char		*line;
	size_t		len_line;
	static char	extra[FD_MAX][BUFFER_SIZE];

	line = malloc(2 * BUFFER_SIZE + 1);
	len_line = append_line(line, extra[fd], strlen(extra[fd]));
	if (extra[fd][len_line])
	{
		memmove(extra[fd], extra[fd] + len_line, BUFFER_SIZE - len_line);
		memset(extra[fd] + BUFFER_SIZE - len_line, 0, len_line);
		return (line);
	}
	get_line_from_fd(line, &len_line, extra[fd], fd);
	if (!len_line)
		return (NULL);
	line[len_line] = 0;
	return (line);
}
