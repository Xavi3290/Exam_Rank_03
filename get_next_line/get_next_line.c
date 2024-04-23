#include <unistd.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif 

int ft_strlen(char *s)
{
	int i = 0;

	while (s[i])
		i++;
	return (i);
}

char *ft_strchr(char *s, int c)
{
	int i = 0;

	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	return (NULL);
}

void ft_strcpy(char *dst, char *ori)
{
	int i = 0;

	while (ori[i])
	{
		dst[i] = ori[i];
		i++;
	}
	dst[i] = '\0';
}

char *ft_strdup(char *s)
{
	int len = ft_strlen(s);
	char *dup = malloc(len + 1);

	if (!dup)
		return (NULL);
	ft_strcpy(dup, s);
	return (dup);
}

char *ft_strjoin(char *s1, char *s2)
{
	int s1_len = ft_strlen(s1);
	int s2_len = ft_strlen(s2);
	char *join = malloc(s1_len + s2_len + 1);

	if (!s1 || !s2)
		return (NULL);
	if (!join)
		return (NULL);
	ft_strcpy(join, s1);
	ft_strcpy(join + s1_len, s2);
	free(s1);
	return (join);
}

char *get_next_line(int fd)
{
	static char buf[BUFFER_SIZE + 1];
	char *line;
	char *newline;
	int bytes;
	int to_copy;

	line = ft_strdup(buf);
	while (!(newline = ft_strchr(line, '\n')) && (bytes = read(fd, buf, BUFFER_SIZE)))
	{
		buf[bytes] = '\0';
		line = ft_strjoin(line, buf);
	}
	if (!ft_strlen(line))
		return (free(line), NULL);
	if (newline)
	{
		to_copy = newline - line + 1;
		ft_strcpy(buf, newline + 1);
	}
	else
	{
		to_copy = ft_strlen(line);
		buf[0] = '\0';	
	}
	line[to_copy] = '\0';
	return (line);
}


/*#include <fcntl.h>
#include <stdio.h>

int main(void)
{
	int fd = open("test.txt", O_RDONLY);
	char *line;	

	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}*/
