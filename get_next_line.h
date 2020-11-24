#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFER_SIZE 9999
# include <stdlib.h>
# include <stdio.h>

int get_next_line(int fd, char **line);

void	*ft_memcpy(void *dst,  const void *src,  size_t n);

void	*ft_memmove(void *dst,  const void *src,  size_t len);


#endif
