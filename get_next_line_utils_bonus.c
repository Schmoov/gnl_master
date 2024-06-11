/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parden <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:32:29 by parden            #+#    #+#             */
/*   Updated: 2024/06/11 17:50:50 by parden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	*my_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*s_dest;
	unsigned char	*s_src;
	size_t			i;

	s_dest = (unsigned char *)dest;
	s_src = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		s_dest[i] = s_src[i];
		i++;
	}
	return ((void *)s_dest);
}

void	*my_memset(void *s, int c, size_t n)
{
	unsigned char	*str;
	size_t			i;

	str = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = (unsigned char)c;
		i++;
	}
	return ((void *)str);
}

char	*my_strdup(const char *s)
{
	char	*dup;
	size_t	size;

	size = 0;
	while (s[size])
		size++;
	size++;
	dup = (char *)malloc(size * sizeof(char));
	if (!dup)
		return (NULL);
	return ((char *)my_memcpy(dup, s, size));
}
