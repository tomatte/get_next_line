/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandao <dbrandao@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 20:07:52 by dbrandao          #+#    #+#             */
/*   Updated: 2022/06/29 20:47:10 by dbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*strdup_by_chr(char	*str, char end, char *a_end)
{
	int		i;
	char	*dup;

	i = 0;
	while (str[i] != end && str[i])
		i++;
	if (str[i])
		i++;
	dup = (char *) malloc(i + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (str[i] != end && str[i])
	{
		dup[i] = str[i];
		i++;
	}
	if (str[i])
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*strdup_by_address(char	*str, char *end)
{
	int		i;
	char	*dup;

	i = 0;
	while (&str[i] != end)
		i++;
	if (str[i])
		i++;
	dup = (char *) malloc(i + 1);
	if (!dup)
		return (NULL);
	i = -1;
	while (&str[++i] != end)
		dup[i] = str[i];
	if (str[i])
		dup[i] = str[i];
	dup[++i] = '\0';
	return (dup);
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

char	*m_join(char *s1, char *buff, ssize_t b_size)
{
	int		i;
	int		j;
	char	*new;

	if (!s1)
	{
		new = strdup_by_address(buff, &buff[b_size - 1]);
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
