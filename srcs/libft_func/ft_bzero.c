/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 09:12:35 by mfilahi           #+#    #+#             */
/*   Updated: 2018/10/18 09:15:06 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/malloc.h"

void *ft_memset(void *s, int c, size_t n)
{
	unsigned char *p;

	p = (unsigned char *)s;
	while (n--)
		*p++ = (unsigned char)c;
	return (s);
}

void ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
