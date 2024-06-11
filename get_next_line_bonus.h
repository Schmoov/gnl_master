#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include <fcntl.h>

# ifndef FD_MAX
#  define FD_MAX 101
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

void	*my_memcpy(void *dest, const void *src, size_t n);
void    *my_memset(void *s, int c, size_t n);
char    *my_strdup(const char *s);
char	*get_next_line(int fd);
#endif
