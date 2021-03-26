/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_zone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 10:06:12 by mfilahi           #+#    #+#             */
/*   Updated: 2021/03/25 18:17:47 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

/*
 ** - ADD NEW MEMORY ZONE TO LIST
*/

void	add_new_zone_to_list(t_mem_zone *new_zone)
{
	t_mem_zone *curr;

	if (!g_head_zone)
		g_head_zone = new_zone;
	else
	{
		curr = g_head_zone;
		while (curr->next)
			curr = curr->next;
		curr->next = new_zone;
	}
}

/*
 ** - REQUEST FROM OS NEW MEMORY ZONE
*/

void	*create_new_zone(size_t pages, size_t type)
{
	size_t		size;
	size_t		zone_size;
	t_mem_zone	*new_zone;

	zone_size = sizeof(t_mem_zone);
	size = (size_t)getpagesize() * pages;
	new_zone = mmap(0, size,
					PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	new_zone->start_zone = (void *)new_zone + zone_size;
	new_zone->zone_size = size - zone_size;
	new_zone->type = type;
	new_zone->next = NULL;
	add_new_zone_to_list(new_zone);
	return (new_zone);
}

/*
 ** - CREATE LARGE ZONE
*/

void	*create_large_zone(size_t total_size)
{
	t_mem_zone	*zone;
	size_t		pages;
	size_t		zone_data_size;

	zone_data_size = sizeof(t_mem_zone);
	pages = (total_size / (size_t)getpagesize()) + 1;
	zone = create_new_zone(pages, LARGE_ZONE);
	return (create_new_block_in_zone(zone, total_size));
}
