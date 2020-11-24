#include "get_next_line.h"

void	*ft_memcpy(void *dst,  const void *src,  size_t n)
{
    size_t i;

    i = 0;
    while (i < n)
    {
        ((char *)dst)[i] = ((char *)src)[i];
        i++;
    }
    return (dst);
}

void	*ft_memmove(void *dst,  const void *src,  size_t len)
{
    if (src < dst)
        while (len--)
            ((char *)dst)[len] = ((char *)src)[len];
    else
        ft_memcpy(dst, src, len);
    return (dst);
}