/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 10:05:11 by mfilahi           #+#    #+#             */
/*   Updated: 2021/03/25 18:22:18 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

/*
 ** - FILL THE FIRST ALLOCATION BLOCK IN A ZONE
*/

void	*fill_first_block(t_mem_zone *zone, size_t total_size)
{
	zone->head_block = zone->start_zone;
	zone->head_block->block_size = total_size;
	zone->head_block->used = TRUE;
	zone->head_block->merged_count = 0;
	zone->head_block->next = NULL;
	zone->tail_block = zone->head_block;
	zone->zone_size -= total_size;
	if (zone->zone_size > total_size)
		zone->start_zone += total_size;
	return (zone->head_block);
}

/*
 ** - FIND FREE BLOCK IN A ZONE
*/

void	*find_free_block_in_zone(t_mem_zone *zone, size_t total_size)
{
	t_block *curr_block;

	curr_block = zone->head_block;
	while (curr_block)
	{
		if (!curr_block->used &&
			curr_block->block_size >= total_size &&
			(curr_block->used = TRUE))
			return (split_merged_blocks(curr_block, total_size));
		curr_block = curr_block->next;
	}
	return (create_new_block_in_zone(zone, total_size));
}

/*
 ** - RESERVE AN ALLOCATION BLOCK
*/

void	*request_block(size_t total_size)
{
	t_mem_zone *tiny_zone;
	t_mem_zone *small_zone;

	tiny_zone = g_head_zone;
	small_zone = g_head_zone->next;
	if (total_size <= MAX_TINY_ZONE_SIZE)
		return (find_free_block_in_zone(tiny_zone, total_size));
	else if (total_size <= MAX_SMALL_ZONE_SIZE)
		return (find_free_block_in_zone(small_zone, total_size));
	else
		return (create_large_zone(total_size));
	return (NULL);
}

/*
 ** - CREATE PREALLOCATED ZONES AND REQUEST AN ALLOCATION
*/

void	*malloc_helper(size_t size)
{
	t_block	*block;
	size_t	node_size;
	size_t	total_size;

	node_size = sizeof(t_block);
	total_size = size + node_size;
	if (!g_head_zone)
	{
		create_new_zone(TINY_ZONE_PAGES, TINY_ZONE);
		create_new_zone(SAMLL_ZONE_PAGES, SMALL_ZONE);
	}
	if (!size)
		return (NULL);
	if (!(block = request_block(total_size)))
		return (NULL);
	return ((void *)((t_block *)block + 1));
}

/*
 ** - ALLOCATE A BLOCK OF MEMORY
*/

void	*malloc(size_t size)
{
	void *block;

	pthread_mutex_lock(&g_lock);
	block = malloc_helper(size);
	pthread_mutex_unlock(&g_lock);
	return (block);
}
