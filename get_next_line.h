/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandao <dbrandao@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 15:48:21 by dbrandao          #+#    #+#             */
/*   Updated: 2022/06/29 20:23:06 by dbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>

char	*get_next_line(int fd);
char	*strdup_by_chr(char	*str, char end);
char	*strdup_by_address(char	*str, char *end);
char	*find_chr(char **str, char c);
char	*m_join(char *s1, char *buff, ssize_t b_size);
void	remove_first_line(char **storage);

#endif