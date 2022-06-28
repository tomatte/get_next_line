/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandao <dbrandao@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 22:28:44 by dbrandao          #+#    #+#             */
/*   Updated: 2022/06/29 00:11:04 by dbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>

typedef struct	s_store
{
	char	*stored;
	int	size;
	int		show_lines;
}				t_store;

char	*get_next_line(int fd);
char	*str_size_chr(char **str, char c);
char	*m_join(char	*str, char	*buffer, ssize_t b_size);
void	store_static(char **m_line, char *buffer, ssize_t bytes_read);
int		read_buffer(int fd, char **m_line, char **end);
void	replace_stored(char **m_stored, char *end);

#endif