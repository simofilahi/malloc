/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 09:58:02 by mfilahi           #+#    #+#             */
/*   Updated: 2021/03/26 09:17:32 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

/*
 ** - CALL MUNMAP TO DEALLOCATE AN ZONE
*/

void	drop_zone(t_block *ptr, t_mem_zone *curr_zone, t_mem_zone *prev_zone)
{
	t_mem_zone	*next_zone;
	size_t		total_size;

	next_zone = curr_zone->next;
	total_size = curr_zone->zone_size + ptr->block_size + sizeof(t_mem_zone);
	if (!(munmap(curr_zone, total_size)))
		prev_zone->next = next_zone;
}

/*
 ** - SET BLOCK FREE
*/

int		free_block(t_mem_zone *curr_zone, t_mem_zone *prev_zone, t_block *ptr)
{
	t_block *curr_block;
	t_block *prev_block;

	curr_block = curr_zone->head_block;
	prev_block = curr_block;
	while (curr_block)
	{
		if (ptr == curr_block && !(curr_block->used = FALSE))
		{
			if (curr_zone->type == LARGE_ZONE)
				drop_zone(ptr, curr_zone, prev_zone);
			else
			{
				ft_bzero(curr_block + 1, ft_strlen((void *)(curr_block + 1)));
				merge_block(curr_block, prev_block);
			}
			return (SUCCESS);
		}
		prev_block = curr_block;
		curr_block = curr_block->next;
	}
	return (FAILED);
}

/*
 ** - SEARCH FOR A BLOCK IF EXIST IN ZONE
*/

void	find_block(t_block *ptr)
{
	t_mem_zone *curr_zone;
	t_mem_zone *prev_zone;

	curr_zone = g_head_zone;
	prev_zone = curr_zone;
	while (curr_zone)
	{
		if (free_block(curr_zone, prev_zone, ptr) == SUCCESS)
			return ;
		prev_zone = curr_zone;
		curr_zone = curr_zone->next;
	}
}

/*
 ** - FREE AN ALLOCATED MEMORY BLOCK
*/

void	free(void *ptr)
{
	t_block *block;

	pthread_mutex_lock(&g_lock);
	if (!ptr)
	{
		pthread_mutex_unlock(&g_lock);
		return ;
	}
	block = (t_block *)ptr - 1;
	find_block(block);
	pthread_mutex_unlock(&g_lock);
}
