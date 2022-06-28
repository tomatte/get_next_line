/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandao <dbrandao@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 18:30:35 by dbrandao          #+#    #+#             */
/*   Updated: 2022/06/28 19:47:27 by dbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	s_len(char *s)
{
	int	i;

	i = 0;
	while (*s++)
		i++;
	return (i);
}

void	store_static(char **m_line, char *buffer, ssize_t bytes_read)
{
	ssize_t	i;
	char	*new;

	if (!*m_line)
	{
		*m_line = (char *) malloc(bytes_read + 1);
		if (!*m_line)
			return ;
		i = -1;
		while (++i < bytes_read)
			*m_line[i] = buffer[i];
		*m_line[i] = '\0';
	}
	else
	{
		i = (ssize_t) s_len(*m_line);
		new = (char *) malloc(bytes_read + i + 1);
		
	}
}

char	*read_buffer(char **m_line)
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
		end = str_size_chr(buffer, bytes_read, '\n');
		store_static(m_line, buffer, bytes_read);
		if (end)
			 break ;
	}
	
}

char	*get_next_line(int fd)
{
	static char	*line = NULL;
	int			bytes_read;


}