/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 09:58:02 by mfilahi           #+#    #+#             */
/*   Updated: 2021/03/25 10:10:38 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

// CALL MUNMAP TO DEALLOCATE AN ZONE
void	dropZone(t_block *ptr, t_memZone *currZone, t_memZone *prevZone)
{
	t_memZone	*nextZone;

	nextZone = currZone->next;
	if (!(munmap(currZone, currZone->zoneSize + ptr->blockSize + sizeof(t_memZone))))
		prevZone->next = nextZone;
}

// SET BLOCK FREE
int		freeBlock(t_memZone *currZone, t_memZone *prevZone, t_block *ptr)
{
	t_block	*currBlock;
	t_block	*prevBlock;

	currBlock = currZone->headBlock;
	prevBlock = currBlock;
	while (currBlock)
	{
		if (ptr == currBlock && !(currBlock->used = FALSE))
		{
			if (currZone->type == LARGE_ZONE)
				dropZone(ptr, currZone, prevZone);
			else
				mergeBlock(currBlock, prevBlock);
			return (SUCCESS);
		}
		prevBlock = currBlock;
		currBlock = currBlock->next;
	}
	return (FAILED);
}

// SEARCH FOR A BLOCK IF EXIST IN ZONE
void findBlock(t_block *ptr)
{
	t_memZone *currZone;
	t_memZone *prevZone;

	currZone = headZone;
	prevZone = currZone;
	while (currZone)
	{
		if (freeBlock(currZone, prevZone, ptr) == SUCCESS)
			return;
		prevZone = currZone;
		currZone = currZone->next;
	}
}

//  FREE AN ALLOCATED MEMORY BLOCK
void free(void *ptr)
{
	t_block *block;

	pthread_mutex_lock(&lock);
	if (!ptr)
	{
		pthread_mutex_unlock(&lock);
		return;
	}
	block = (t_block *)ptr - 1;
	findBlock(block);
	pthread_mutex_unlock(&lock);
}
