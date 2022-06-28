/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandao <dbrandao@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 14:09:55 by dbrandao          #+#    #+#             */
/*   Updated: 2022/06/28 18:14:33 by dbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	initialize_store(t_store **store)
{
	if (!*store)
	{
		*store = (t_store *) malloc(sizeof(t_store));
		if (!*store)
			return ;
		(*store)->stored = NULL;
		(*store)->size = 0;
		(*store)->show_lines = 0;
	}
	(*store)->show_lines++;
}

char	*str_size_chr(char *str, size_t size, char c)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (str[i] == c)
			return (str);
		i++;
	}
	return (NULL);
}

void	store_buffer(t_store *store, char *buffer, int b_size)
{
	char	*aux;
	int		i;
	int		j;

	aux = (char *) malloc(store->size + b_size + 1);
	i = -1;
	while (++i < store->size)
		aux[i] = store->stored[i];
	j = -1;
	while (++j < b_size)
		aux[i + j] = buffer[j];
	aux[i + j] = '\0';
	if (store->stored)
		free(store->stored);
	store->stored = aux;
}

int	read_line(int fd, t_store *store)
{
	char			*buffer;
	int				bytes_read;

	buffer = (char *) malloc(BUFFER_SIZE);
	bytes_read = 0;
	while (1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (!bytes_read)
			break ;
		store_buffer(store, buffer, bytes_read);
		if (str_size_chr(buffer, bytes_read, '\n'))
			break ;
	}
	return (bytes_read );
}

char	*get_next_line(int fd)
{
	static	t_store	*s = NULL;
	char	*text;
	int		i;
	int		lines;
	char	*end;

	initialize_store(&s);
	if (!read_line(fd, s))
		return (s->stored);

	i = 0;
	lines = s->show_lines;
	while (lines)
	{
		if (s->stored[i] == '\n')
			lines--;
		i++;
	}

	return (text);
}

#include <stdio.h>
#include <fcntl.h>
int	main(void)
{
	char	*line;
	int		fd;

	fd = open("./info.txt", O_RDONLY);
	line = get_next_line(fd);
	printf("%s\n", line);
}

/*

123
123456

buff = 123\n1
static = 
*/