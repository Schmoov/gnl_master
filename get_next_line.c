/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parden <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 12:39:12 by parden            #+#    #+#             */
/*   Updated: 2024/06/09 17:43:42 by parden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

void	get_line_from_fd(char **line, size_t *len_line, char *stash, int fd)
{
	char	buf[BUFFER_SIZE];
	int		bytes_read;
	size_t	size_line;

	bytes_read = BUFFER_SIZE;
	size_line = BUFFER_SIZE + 1;

	while ((!*len_line || (*line)[*len_line - 1] != '\n') && bytes_read == BUFFER_SIZE)
	{
		if (*len_line + 1 + BUFFER_SIZE > size_line)
			my_realloc(line, &size_line, *len_line);
		if (!*line)
		{
			*len_line = 0;
			return ;
		}
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read != -1)
			*len_line += append_line(*line + *len_line, buf, bytes_read);
	}
	if (bytes_read == -1)
		*len_line = 0;
	save_stash(stash, buf, bytes_read);
}

size_t	fill_from_stash(char *line, char *stash)
{
	size_t	len_line;

	len_line = append_line(line, stash, strlen(stash));
	memmove(stash, stash + len_line, BUFFER_SIZE - len_line);
	memset(stash + BUFFER_SIZE - len_line, 0, len_line);
	return (len_line);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*res;
	size_t		len_line;
	static char	stash[BUFFER_SIZE];

	if (fd < 0)
		return (NULL);
	line = malloc(BUFFER_SIZE + 1);
	if (!line)
		return (NULL);
	len_line = fill_from_stash(line, stash);
	if (!len_line || line[len_line - 1] != '\n')
		get_line_from_fd(&line, &len_line, stash, fd);
	if (!len_line)
	{
		free(line);
		return (NULL);
	}
	line[len_line] = 0;
	res = strdup(line);
	free(line);
	return (res);
}
