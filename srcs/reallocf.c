/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reallocf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 11:20:01 by mfilahi           #+#    #+#             */
/*   Updated: 2021/03/25 12:17:32 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	*reallocf(void *ptr, size_t size)
{
	void *block;

	pthread_mutex_lock(&lock);
	block = realloc(ptr, size);
	free(ptr);
	pthread_mutex_unlock(&lock);
	return (block);
}
