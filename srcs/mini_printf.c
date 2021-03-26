/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_printf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 11:00:10 by mfilahi           #+#    #+#             */
/*   Updated: 2021/03/25 11:00:56 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	print_address_hex(unsigned long n)
{
	unsigned long	base;

	base = 16;
	if (n > 0)
		print_address_hex(n /= base);
	if ((n % base) >= 10)
		ft_putchar((n % base) + 'a' - 10);
	else
		ft_putchar((n % base) + '0');
}

void	min_printf(void *str, void *ptr, int nflag)
{
	if (str)
		ft_putstr(str);
	if (ptr)
	{
		ft_putstr("0x");
		print_address_hex((((unsigned long)ptr) * 16));
	}
	if (nflag)
		ft_putchar('\n');
}
