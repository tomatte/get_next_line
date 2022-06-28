/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandao <dbrandao@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 18:30:35 by dbrandao          #+#    #+#             */
/*   Updated: 2022/06/28 22:15:49 by dbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*str_size_chr(char **str, char c)
{
	int	i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == c)
			return (&(*str)[i]);
		i++;
	}
	return (NULL);
}

char	*m_join(char	*str, char	*buffer, ssize_t b_size)
{
	ssize_t	i;
	ssize_t	j;
	char	*new;

	i = 0;
	while (str[i])
		i++;
	new = (char *) malloc(i + b_size + 1);
	if (!new)
		return (NULL);
	i = -1;
	while (str[++i])
		new[i] = str[i];
	j = -1;
	while (++j < b_size)
		new[j + i] = buffer[j];
	new[j + i] = '\0';
	return (new);
}
#include <stdio.h>
void	store_static(char **m_line, char *buffer, ssize_t bytes_read)
{
	ssize_t	i;
	char	*new;

	if (!*m_line)
	{
		*m_line = (char *) malloc(bytes_read + 1);
		if (!*m_line)
			return ;
		i = 0;
		while (i < bytes_read)
		{
			(*m_line)[i] = buffer[i];
			i++;
		}
		(*m_line)[i] = '\0';
	}
	else
	{
		new = m_join(*m_line, buffer, bytes_read);
		printf("join: %s\n", new);
		if (!new)
			return ;
		free(*m_line);
		*m_line = new;
	}
}

char	*read_buffer(int fd, char **m_line)
{
	char		*buffer;
	char		*end;
	ssize_t		bytes_read;

	buffer = (char *) malloc(BUFFER_SIZE);
	if (!buffer)
		return (NULL);
	while (1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		store_static(m_line, buffer, bytes_read);
		end = str_size_chr(m_line, '\n');
		if (end)
			break ;
	}
	return (end);
}

void	replace_static(char **m_stored, char *end)
{
	
}

char	*get_next_line(int fd)
{
	static char	*stored = NULL;
	char		*one_line;
	char		*end;
	int			bytes_read;
	int			i;

	end = read_buffer(fd, &stored);
	if (!end)
		return (stored);
	i = 0;
	while (&stored[i] != end)
		i++;
	one_line = (char *) malloc(i + 2);
	if (!one_line)
		return (NULL);
	i = -1;
	while (&stored[++i] != end)
		one_line[i] = stored[i];
	one_line[i] = stored[i];
	one_line[i+1] = '\0';
	replace_stored(&stored, end);
	return (one_line);
}

#include <stdio.h>
#include <fcntl.h>
int	main(void)
{
	char	*line;
	int		fd;

	fd = open("./info.txt", O_RDONLY);
	line = get_next_line(fd);
	printf("main:%s\n", line);
	line = get_next_line(fd);
	printf("main: %s\n", line);
	return (0);
}