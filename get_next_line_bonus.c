/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandao <dbrandao@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 22:09:49 by dbrandao          #+#    #+#             */
/*   Updated: 2022/06/29 22:21:25 by dbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	verify_line(char **storage, char **single_line)
{
	if (!*storage)
		return (0);
	if (!find_chr(storage, '\n'))
		return (0);
	*single_line = strdup_flex(*storage, '\n', NULL);
	if (!*single_line)
		return (-1);
	remove_first_line(storage);
	return (1);
}

void	store_in_static(char **storage, char *buffer, ssize_t b_size)
{
	char	*new;

	new = m_join(*storage, buffer, b_size);
	if (!new)
		return ;
	free(*storage);
	*storage = new;
}

int	no_return(char *storage, char *buffer, ssize_t r_bytes)
{
	if (r_bytes < 0)
	{
		free(buffer);
		return (-1);
	}
	if (!storage && !r_bytes)
	{
		free(buffer);
		return (0);
	}
	if (storage && !r_bytes)
	{
		free(buffer);
		return (2);
	}
	return (1);
}

int	read_buffer(int fd, char **storage, char **s_line)
{
	char	*buffer;
	int		r_bytes;
	int		flag;

	buffer = (char *) malloc(BUFFER_SIZE);
	if (!buffer)
		return (0);
	while (1)
	{
		r_bytes = read(fd, buffer, BUFFER_SIZE);
		flag = no_return(*storage, buffer, r_bytes);
		if (flag != 1)
			return (flag);
		store_in_static(storage, buffer, r_bytes);
		flag = verify_line(storage, s_line);
		if (flag)
		{
			free(buffer);
			return (flag);
		}
	}
}

char	*get_next_line(int fd)
{
	static char	*storage[1024];
	char		*single_line;
	int			flag;

	if (!storage[fd])
		storage[fd] = NULL;
	flag = verify_line(&storage[fd], &single_line);
	if (flag == 1)
		return (single_line);
	else if (flag == -1)
		return (NULL);
	flag = read_buffer(fd, &storage[fd], &single_line);
	if (flag == 1)
		return (single_line);
	else if (flag == 2)
	{
		single_line = strdup_flex(storage[fd], '\0', NULL);
		del(&storage[fd]);
		if (!single_line)
			return (NULL);
		return (single_line);
	}
	if (storage[fd])
		del(&storage[fd]);
	return (NULL);
}

/* 
#include <stdio.h>
#include <fcntl.h>
  int main(void)
{
    int		fd;
	int		fd2;
    char    *buf;
	char	*buf2;

    fd = open("./opa.txt", O_RDONLY);
    while (1)
    {
        buf = get_next_line(fd);
        if (!buf)
            break;
		printf("%s", buf);
        free(buf);
    }
    fd2 = open("./info.txt", O_RDONLY);
    while (1)
    {
        buf2 = get_next_line(fd2);
        if (!buf2)
            break;
		printf("%s", buf2);
        free(buf2);
    }
    close(fd2);
	printf("\n");
    return (0);
}
 */
/*
verificar se ja foi lido
ler com um buffer : se for lido 0 bytes...
armazenar em storage
verificar se tem quebra de linha
	falso? do again

	verdadeiro?
		criar uma nova string até a quebra de linha pra ser retornada no final
		remove_from_storage()

remove_from storage()
{
	deixar no buffer apenas o que nao sera retornado:
		criar uma nova string aux apartir da quebra de linha
		liberar storage
		atribuir aux à storage
}

...se for lido 0 bytes no buffer
	se storage for NULL, retornar NULL

	criar uma nova string com o que tiver restado em storage
	liberar storage
	atribuir NULL à storage


necessário:
	join pra juntar storage e buffer, se storage for null, usa apenas o buffer
	
	dup: pra criar nova string que terminará 
	apṕs o \n ou no \0 caso nao tiver quebra de linha
*/