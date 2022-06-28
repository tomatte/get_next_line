/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandao <dbrandao@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 14:09:39 by dbrandao          #+#    #+#             */
/*   Updated: 2022/06/28 16:14:58 by dbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
}

#include <stdio.h>
int	main(void)
{
	static t_store *store = NULL;
	printf("%p\n", store);
	initialize_store(&store);
	printf("%d\n", store->size);
}