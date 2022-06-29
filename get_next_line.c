/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandao <dbrandao@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 15:50:36 by dbrandao          #+#    #+#             */
/*   Updated: 2022/06/29 19:04:57 by dbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*m_strdup(char	*str, char end, int size)
{
	int		i;
	char	*dup;

	i = 0;
	while (str[i] != end)
		i++;
	if (end)
		i++;
	dup = (char *) malloc(i + 1);
	if (!dup)
		return (NULL);
	i = -1;
	while (str[++i] != end)
		dup[i] = str[i];
	if (end)
		dup[++i] = end;
	dup[++i] = '\0';
	return (dup);
}

char	*last_call(char **storage)
{
	char	*line;

	line = m_strdup(*storage, '\0', 0);
	if (!line)
		return (NULL);
	free(*storage);
	*storage = NULL;
	return (line);
}

char	*find_chr(char **str, char c)
{
	int	i;

	i = 0;
	while ((*str)[i] != c && (*str)[i])
		i++;
	if ((*str)[i] == c)
		return (&(*str)[i]);
	return (NULL);
}

void	remove_first_line(char **storage)
{
	char	*begin;
	char	*new;
	int		i;

	begin = find_chr(storage, '\n');
	begin++;
	i = 0;
	while (begin[i])
		i++;
	new = (char *) malloc(i + 1);
	if (!new)
		return ;
	i = -1;
	while (begin[++i])
		new[i] = begin[i];
	new[i] = '\0';
	free(*storage);
	*storage = new;
}

int	verify_line(char **storage, char **single_line)
{
	if (!*storage)
		return (0);
	if (!find_chr(storage, '\n'))
		return (0);
	*single_line = m_strdup(*storage, '\n');
	if (!*single_line)
		return (-1);
	remove_first_line(storage);
	return (1);
}

char	*m_join(char *s1, char *buff, ssize_t b_size)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	if (!s1)
	{
		new = m_strdup(buff, '\0', &buff[b_size - 1]);
		if (!new)
			return (NULL);
		return (new);
	}
	i = 0;
	while (s1[i])
		i++;
	new = (char *) malloc(i + b_size + 1);
	if (!new)
		return (NULL);
	i = -1;
	while (s1[++i])
		new[i] = s1[i];
	j = -1;
	while (++j < b_size)
		new[i + j] = buff[j];
	new[i + j] = '\0';
	return (new);
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
		if (!*storage && !r_bytes)
			return (0);
		if (*storage && !r_bytes)
			return (2);
		store_in_static(storage, buffer, r_bytes);
		flag = verify_line(storage, s_line);
		if (flag)
			return (flag);
	}
}

char	*get_next_line(int fd)
{
	static char	*storage = NULL;
	char		*single_line;
	int			flag;

	flag = verify_line(&storage, &single_line);
	if (flag == 1)
		return (single_line);
	else if (flag == -1)
		return (NULL);
	flag = read_buffer(fd, &storage, &single_line);
	if (!flag || flag == -1)
		return (NULL);
	if (flag == 1)
		return (single_line);
	if (flag == 2)
	{
		single_line = last_call(&storage);
		if (!single_line)
			return (NULL);
		return (single_line);
	}
}

#include <fcntl.h>
#include <stdio.h>
int	main(void)
{
	int 	fd;
	char	*line;

	fd = open("./opa.txt", O_RDONLY);
	line = get_next_line(fd);
	printf("%s\n", line);
}

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
	dup: pra criar nova string que terminará apṕs o \n ou no \0 caso nao tiver quebra de linha
*/