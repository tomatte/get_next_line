/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandao <dbrandao@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 14:09:55 by dbrandao          #+#    #+#             */
/*   Updated: 2022/06/28 15:38:45 by dbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	initialize_store(t_store *store)
{
	if (!store)
	{
		store = (t_store *) malloc(sizeof(t_store));
		if (!store)
			return ;
		store->stored = NULL;
		store->size = 0;
		store->show_lines = 0;
	}
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

	aux = (char *) malloc(store->size + b_size);
	i = 0;
	while (i < store->size)
	{
		aux[i] = store->stored[i];
		i++;
	}
	j = 0;
	while (j < b_size)
	{
		aux[i] = buffer[j];
		i++;
		j++;
	}
	if (store->stored)
		free(store->stored);
	store->stored = aux;
}

void	read_line(int fd, t_store *store)
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
		{
			store->show_lines++;
			break ;
		}
	}
}

char	*get_next_line(int fd)
{
	static t_store	*s = NULL;

	initialize_store(s);
	read_line(fd, s);
	return (s->stored);
}

#include <stdio.h>
#include <fcntl.h>
int	main(void)
{
	char	*line;
	int		fd;

	fd = open("./info.txt", O_RDONLY);
	line = get_next_line(fd);
	write(1, line, 50);
}