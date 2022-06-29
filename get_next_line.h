/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandao <dbrandao@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 15:48:21 by dbrandao          #+#    #+#             */
/*   Updated: 2022/06/29 21:27:36 by dbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>

char	*get_next_line(int fd);
char	*find_chr(char **str, char c);
char	*m_join(char *s1, char *buff, ssize_t b_size);
void	remove_first_line(char **storage);
char	*strdup_flex(char	*str, char end, char *a_end);
void	del(char	**mem);

#endif