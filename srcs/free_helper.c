/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 10:45:41 by mfilahi           #+#    #+#             */
/*   Updated: 2021/03/27 15:22:01 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

/*
 ** - MERGE TWO FREE BLOCK
*/

void	merge_block(t_mem_zone *zone, t_block *curr_block, t_block *prev_block)
{
	if ((prev_block != curr_block) &&
			(!prev_block->used && !curr_block->used))
	{
		prev_block->block_size += curr_block->block_size;
		prev_block->alloc_size += (curr_block->alloc_size - sizeof(t_block));
		prev_block->next = curr_block->next;
		if (curr_block == zone->tail_block)
			zone->tail_block = prev_block;
	}
}
