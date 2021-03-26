/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 10:47:32 by mfilahi           #+#    #+#             */
/*   Updated: 2021/03/26 10:03:13 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

/*
 ** - FILL AN ALLOCATION BLOCK
*/

void	*fill_block(t_mem_zone *zone, size_t total_size)
{
	t_block *block;

	block = zone->start_zone;
	block->block_size = total_size;
	block->used = TRUE;
	block->merged_count = 0;
	block->next = NULL;
	zone->tail_block->next = block;
	zone->tail_block = zone->tail_block->next;
	zone->zone_size -= total_size;
	if (zone->zone_size > total_size)
		zone->start_zone += total_size;
	return (block);
}

/*
 ** - SEARCH FOR EXTRA ZONE THAT WILL HOLD AN ALLOCATION
*/

void	*get_empty_extra_zone(size_t total_size)
{
	t_mem_zone *curr_zone;
	t_mem_zone *zone;

	curr_zone = g_head_zone;
	while (curr_zone)
	{
		if (curr_zone->zone_size >= total_size && curr_zone->type == EXTRA_ZONE)
			return (create_new_block_in_zone(curr_zone, total_size));
		curr_zone = curr_zone->next;
	}
	zone = create_new_zone(EXTRA_ZONE_PAGES, EXTRA_ZONE);
	return (create_new_block_in_zone(zone, total_size));
}

/*
 ** - LOOK IN EXTRA ZONE IF THERE IS A FREE BLOCK
*/

void	*find_free_block_in_extra_zone(size_t total_size)
{
	t_block		*curr_block;
	t_mem_zone	*curr_zone;

	curr_zone = g_head_zone;
	while (curr_zone)
	{
		if (curr_zone->type == EXTRA_ZONE)
		{
			curr_block = curr_zone->head_block;
			while (curr_block)
			{
				if (!curr_block->used &&
					curr_block->block_size >= total_size &&
					(curr_block->used = TRUE))
					return (curr_block);
				curr_block = curr_block->next;
			}
		}
		curr_zone = curr_zone->next;
	}
	return (get_empty_extra_zone(total_size));
}

/*
 ** - CREATE NEW BLOCK IN A ZONE
*/

void	*create_new_block_in_zone(t_mem_zone *zone, size_t total_size)
{
	if (zone->zone_size > total_size)
	{
		if (!zone->head_block)
			return (fill_first_block(zone, total_size));
		else
			return (fill_block(zone, total_size));
	}
	else
		return (find_free_block_in_extra_zone(total_size));
	return (NULL);
}
