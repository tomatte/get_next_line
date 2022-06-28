/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandao <dbrandao@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 18:30:35 by dbrandao          #+#    #+#             */
/*   Updated: 2022/06/29 00:19:04 by dbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*stored = NULL;
	char		*one_line;
	char		*end;
	int			bytes_read;
	int			i;

	if (!read_buffer(fd, &stored, &end))
	{
		if (stored)
			free(stored);
		return (NULL);
	}
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
	one_line[i + 1] = '\0';
	replace_stored(&stored, end);
	return (one_line);
}
