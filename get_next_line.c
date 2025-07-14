#include "get_next_line.h"
#include <string.h>

static char	*ft_strchr(char *s, int c)
{
	unsigned int	i;
	char			cc;

	cc = (char) c;
	i = 0;
	while (s[i])
	{
		if (s[i] == cc)
			return ((char *) &s[i]);
		i++;
	}
	if (s[i] == cc)
		return ((char *) &s[i]);
	return (NULL);
}
size_t	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char *ft_strdup(char *str)
{
	char *dst;
	unsigned int i = 0;

	dst = (char *)malloc(ft_strlen(str) + 1);
	if (!dst)
		return(NULL);
	while(str[i])
	{
		dst[i] = str[i];
		i++;
	}
	dst[i] = 0;
	return(dst);
}

char *ft_strjoin(char *s1, char *s2)
{
	char *res;
	unsigned int i = 0;
	unsigned int j = 0;

	res = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!res)
		return(NULL);
	while (s1[j])
		res[i++] = s1[j++];
	j = 0;
	while (s2[j])
		res[i++] = s2[j++];
	res[i] = 0;
	return(res);
}

static char *fill_line(int fd, char *left_c, char *buffer)
{
	ssize_t b_read = 1;
	char *tmp;

	while(b_read > 0)
	{
		b_read = read(fd, buffer, BUFFER_SIZE);
		if  (b_read == -1)
		{
			free(left_c);
			return(NULL);
		}
		else if (b_read == 0)
			break;
		buffer[b_read] = 0;
		if (!left_c)
			left_c = ft_strdup("");
		tmp = left_c;
		left_c = ft_strjoin(tmp, buffer);
		free(tmp);
		tmp = NULL;
		if (strchr(buffer, '\n'))
			break ;
	}
	return(left_c);
}

char *ft_substr(char *s, unsigned int start,  size_t len)
{
	size_t i = 0;
	char *str;

	if (!s)
		return(NULL);
	if (start > ft_strlen(s))
		return(malloc(1));
	if (len > ft_strlen(s + start) )
		len = ft_strlen(s + start);
	str = malloc ((len + 1) * sizeof(char));
	if (!str)
		return(NULL);
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = 0;
	return(str);
}

static char *set_line(char *line_buff)
{
	char *left_c;
	ssize_t i = 0;

	while (line_buff[i] != '\n' && line_buff[i] != '\0')
		i++;
	if (line_buff[i] == 0 || line_buff[1] == 0)
		return(NULL);
	left_c = ft_substr(line_buff, i + 1, ft_strlen(line_buff) - i);
	if (*left_c == 0)
	{
		free(left_c);
		left_c = NULL;
	}
	line_buff[i + 1] = 0;
	return(left_c);
}

char *get_next_line(int fd)
{
	if (fd < 0 || BUFFER_SIZE <= 0)
		return(NULL);
	static char *left_c;
	char *line;
	char *buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));

	if (!buffer)
		return(NULL);
	line = fill_line(fd, left_c, buffer);
	free(buffer);
	buffer = NULL;
	if (!line)
		return(NULL);
	left_c = set_line(line);
	return(line);
}