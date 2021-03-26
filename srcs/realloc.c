/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 11:01:09 by mfilahi           #+#    #+#             */
/*   Updated: 2021/03/26 14:33:58 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

/*
 ** - LOOK FOR A BLOCK IF EXIST IN A ZONE
*/

static t_block	*find_block(t_block *ptr)
{
	t_mem_zone	*curr_zone;
	t_block		*curr_block;

	curr_zone = g_head_zone;
	while (curr_zone)
	{
		curr_block = curr_zone->head_block;
		while (curr_block)
		{
			if (ptr == curr_block)
				return (curr_block);
			curr_block = curr_block->next;
		}
		curr_zone = curr_zone->next;
	}
	return (NULL);
}

/*
 ** - REALLOC HELPER
*/

void			*realloc_helper(void *ptr, size_t size)
{
	void	*block;
	t_block	*targeted_block;
	size_t	len;

	block = NULL;
	if (!ptr)
		return (malloc(size));
	if ((targeted_block = find_block((t_block *)ptr - 1)))
	{
		len = 0;
		if (targeted_block->block_size > size)
			len = size;
		else
			len = targeted_block->block_size;
		if (!(block = (malloc(size))))
			return (block);
		ft_memcpy(block, ptr, len);
		free(ptr);
	}
	return (block);
}

/*
 ** - REALLOC AN ALLOCATION
*/

void			*realloc(void *ptr, size_t size)
{
	void	*block;

	pthread_mutex_lock(&g_lock);
	block = realloc_helper(ptr, size);
	pthread_mutex_unlock(&g_lock);
	return (block);
}
