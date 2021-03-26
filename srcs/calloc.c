/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 09:56:58 by mfilahi           #+#    #+#             */
/*   Updated: 2021/03/26 14:32:56 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	*calloc(size_t count, size_t size)
{
	void	*ptr;

	pthread_mutex_lock(&g_lock);
	ptr = malloc(count * size);
	ft_bzero(ptr, count * size);
	pthread_mutex_unlock(&g_lock);
	return (ptr);
}
