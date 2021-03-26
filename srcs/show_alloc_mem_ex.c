/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem_ex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 11:09:06 by mfilahi           #+#    #+#             */
/*   Updated: 2021/03/25 18:15:05 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

/*
 ** - PRINT ZONES NAME
*/

static void	print_zones_name(t_mem_zone *curr_mem_zone)
{
	if (curr_mem_zone->type == TINY_ZONE)
		min_printf("TINY : ", curr_mem_zone, 0);
	else if (curr_mem_zone->type == SMALL_ZONE)
		min_printf("SMALL : ", curr_mem_zone, 0);
	else if (curr_mem_zone->type == EXTRA_ZONE)
		min_printf("EXTRA : ", curr_mem_zone, 0);
	else
		min_printf("LARGE : ", curr_mem_zone, 0);
	ft_putstr(", ");
	ft_putnbr((long)curr_mem_zone->zone_size);
	ft_putendl(" bytes ");
}

/*
 ** - CALCULATE BLOCK SIZE
*/

void		calculateblock_size(t_block *curr, size_t *block_size)
{
	size_t block_size_count;

	block_size_count = (sizeof(t_block) * (curr->merged_count + 1));
	if (!curr->merged_count)
	{
		if (block_size_count > curr->block_size)
			*block_size = 0;
		else
			*block_size = curr->block_size - sizeof(t_block);
	}
	else
	{
		if (block_size_count > curr->block_size)
			*block_size = 0;
		else
			*block_size = curr->block_size - block_size_count;
	}
}

/*
 ** - PRINT BLOCK INFORMATION
*/

static void	print_blocks_infos(t_block *curr, size_t *total_size)
{
	size_t block_size;

	calculateblock_size(curr, &block_size);
	min_printf("   -> BLOCK          : ", curr + 1, 0);
	min_printf(" - ", (((void *)(curr + 1)) + block_size), 1);
	ft_putstr("     - USED          : ");
	if (curr->used)
		ft_putendl("YES");
	else
		ft_putendl("NO");
	ft_putstr("     - SIZE          : ");
	ft_putnbr((long)block_size);
	ft_putendl(" bytes");
	*total_size += block_size;
}

/*
 ** - DISPLAY MORE DETAILS ABOUT ALLOCATION
*/

void		show_alloc_mem_ex(void)
{
	t_mem_zone	*curr_mem_zone;
	t_block		*curr;
	size_t		total_size;

	pthread_mutex_lock(&g_lock);
	curr_mem_zone = g_head_zone;
	total_size = 0;
	ft_putstr("\n*************************************\n");
	while (curr_mem_zone)
	{
		print_zones_name(curr_mem_zone);
		curr = curr_mem_zone->head_block;
		while (curr)
		{
			print_blocks_infos(curr, &total_size);
			curr = curr->next;
		}
		curr_mem_zone = curr_mem_zone->next;
	}
	ft_putstr("Total: ");
	ft_putnbr((long)total_size);
	ft_putendl(" bytes");
	ft_putstr("*************************************\n");
	pthread_mutex_unlock(&g_lock);
}
