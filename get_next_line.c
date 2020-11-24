#include <io.h>
#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
    size_t i;

    i = 0;
    while (s[i])
        i++;
    return (i);
}



char *search_nl(char *buff)
{
    size_t i;
    size_t len;

    i = 0;
    len = ft_strlen(buff);
    while (i < len)
    {
        if (buff[i] == '\n')
            return (buff + i);
        i++;
    }
    return (0);
}

int expand_buff(char **buff, int fd){
    char *tmp;
    size_t prev_len;
    int r;

    if (!*buff)
    {
        *buff = (char *)malloc(BUFFER_SIZE + 1);
        r = read(fd, *buff, BUFFER_SIZE);
        (*buff)[r] = '\0';
        if (!r)
            free(*buff);
        return (r);
    }
    prev_len = ft_strlen(*buff);
    tmp = (char *)malloc(prev_len + BUFFER_SIZE + 1);
    if (!tmp)
        return (-1);
    ft_memcpy(tmp, *buff, prev_len);
    r = read(fd, tmp + prev_len, BUFFER_SIZE);
    tmp[prev_len + r] = '\0';
    free(*buff);
    *buff = tmp;
    if (ft_strlen(tmp) == 0){
        free (tmp);
        *buff = 0;
        return (0);
    }
    if (prev_len == ft_strlen(tmp))
        return (-2);
    return (1);
}

int set_line(char *buff, char **line, char *nl)
{
    size_t line_len;
    size_t buff_len;

    line_len = nl - buff;
    buff_len = ft_strlen(buff);
    *line = (char *)malloc(line_len + 1);
    if (!*line)
        return (-1);
    ft_memcpy(*line, buff, line_len);
    (*line)[line_len] = '\0';
    ft_memmove(buff, nl + 1, buff_len - line_len);
    buff[buff_len - line_len] = '\0';
    return (1);
}

int get_next_line(int fd, char **line) {
    static char *buffs[1024];
    char *nl;
    int signal;

    if (!buffs[fd])
    {
        signal = expand_buff(buffs + fd, fd);
        if (signal <= 0)
            return (signal);
    }
    while (!(nl = search_nl(buffs[fd])))
    {
        signal = expand_buff(buffs + fd, fd);
        if (signal == 0 || signal == -1)
            return (signal);
        if (signal == -2)
        {
            nl = buffs[fd] + ft_strlen(buffs[fd]);
            break;
        }
    }
    if (!set_line(buffs[fd], line, nl))
        return (-1);
    return (1);
}