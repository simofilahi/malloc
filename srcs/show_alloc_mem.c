/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 11:06:39 by mfilahi           #+#    #+#             */
/*   Updated: 2021/03/25 18:13:54 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

/*
 ** - PRINT MEMORY ZONE NAME
*/

void	print_mem_names(t_mem_zone *curr_mem_zone)
{
	if (curr_mem_zone->type == TINY_ZONE)
		min_printf("TINY : ", curr_mem_zone, 1);
	else if (curr_mem_zone->type == SMALL_ZONE)
		min_printf("SMALL: ", curr_mem_zone, 1);
	else if (curr_mem_zone->type == EXTRA_ZONE)
		min_printf("EXTRA: ", curr_mem_zone, 1);
	else
		min_printf("LARGE: ", curr_mem_zone, 1);
}

/*
 ** - PRINT MEMORY BLOCK INFORMATION
*/

void	print_blocks_infos(t_block *curr, size_t *total_size)
{
	size_t block_size;

	block_size = 0;
	while (curr)
	{
		if (curr->used)
		{
			calculateblock_size(curr, &block_size);
			min_printf("", curr + 1, 0);
			min_printf(" - ", (((void *)(curr + 1)) + block_size), 0);
			ft_putstr(" : ");
			ft_putnbr((long)block_size);
			min_printf(" bytes", NULL, 1);
			*total_size += block_size;
		}
		curr = curr->next;
	}
}

/*
 ** - DISPLAY MEMORY ALLOCATION DETAILS
*/

void	show_alloc_mem(void)
{
	t_mem_zone	*curr_mem_zone;
	size_t		total_size;

	pthread_mutex_lock(&g_lock);
	curr_mem_zone = g_head_zone;
	total_size = 0;
	while (curr_mem_zone)
	{
		print_mem_names(curr_mem_zone);
		print_blocks_infos(curr_mem_zone->head_block, &total_size);
		curr_mem_zone = curr_mem_zone->next;
	}
	ft_putstr("Total: ");
	ft_putnbr((long)total_size);
	ft_putendl(" bytes");
	pthread_mutex_unlock(&g_lock);
}
