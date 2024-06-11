/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parden <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 12:39:12 by parden            #+#    #+#             */
/*   Updated: 2024/06/11 12:39:03 by parden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	unload_buffer(char *line, char *buf)
{
	size_t	i;
	size_t	added_to_line;

	i = 0;
	while (i < BUFFER_SIZE && (!i || line[i - 1] != '\n') && buf[i] != 0)
	{
		line[i] = buf[i];
		i++;
	}
	added_to_line = i;
	while (i <

	return (added_to_line);
}

void	my_realloc(char **line, size_t *size_line, size_t len_line)
{
	char *res;

	if (!*size_line)
	{
		*line = malloc(BUFFER_SIZE + 1);
		*size_line = BUFFER_SIZE + 1;
		return ;
	}
	res = malloc(*size_line * 2);
	if (!res)
	{
		free(*line);
		*line = NULL;
		return ;
	}
	memcpy(res, *line, len_line);
	free(*line);
	*size_line *= 2;
	*line = res;
}

void	save_stash(char *stash, char *buf, int bytes_read)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < bytes_read && buf[i] != '\n')
		i++;
	i++;
	while (i < bytes_read)
	{
		stash[j] = buf[i];
		i++;
		j++;
	}
	while (j < BUFFER_SIZE)
	{
		stash[j] = 0;
		j++;
	}
}

void	load_buffer(char *stash, int fd)
{
	int		bytes_read;

	bytes_read = read(fd, stash, BUFFER_SIZE);
	if (bytes_read != -1)
		*len_line = 0;
}

size_t	unload_buffer(char *line, char *stash)
{
	size_t	len_line;

	len_line = append_line(line, stash, strlen(stash));
	memmove(stash, stash + len_line, BUFFER_SIZE - len_line);
	memset(stash + BUFFER_SIZE - len_line, 0, len_line);
	return (len_line);
}

char	*populate_line(char *buffer, int *len_line, int *size_line)
{
	char	*line;
	int		bytes_read;

	while (!len_line || line[len_line - 1] != '\n')
	{
		if (len_line + 1 + BUFFER_SIZE > size_line)
			my_realloc(line, &size_line, *len_line);
		if (!*line)
			return (NULL);
		len_line += append_line(line, buffer, strlen(buffer));
		bytes_read = read(fd, stash, BUFFER_SIZE);
	}

char	*get_next_line(int fd)
{
	char		*line;
	char		*res;
	size_t		len_line;
	size_t		size_line;
	static char	stash[FD_MAX][BUFFER_SIZE];

	if (fd < 0 || fd >= FD_MAX)
		return (NULL);
	size_line = 0;
	len_line = 0;
	line[len_line] = 0;
	res = strdup(line);
	free(line);
	return (res);
}
