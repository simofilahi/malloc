/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 09:16:01 by mfilahi           #+#    #+#             */
/*   Updated: 2021/03/25 11:16:55 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/malloc.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char *d;
	char *s;

	d = (char *)dst;
	s = (char *)src;
	if (d == s || n == 0)
		return (d);
	while (n--)
		*d++ = *s++;
	return (dst);
}
