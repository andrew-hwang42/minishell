/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahwang <ahwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 06:03:54 by ahwang            #+#    #+#             */
/*   Updated: 2025/03/04 06:24:48 by ahwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	check_args(char c, va_list ap, int *len)
{
	if (c == 'c')
		*len += ft_putchar(va_arg(ap, int));
	else if (c == 's')
		*len += ft_putstr(va_arg(ap, char *));
	else if (c == 'p')
		*len += ft_pointer(va_arg(ap, unsigned long));
	else if (c == 'd' || c == 'i')
		*len += ft_putnbr(va_arg(ap, int));
	else if (c == 'u')
		*len += ft_unsigned_int(va_arg(ap, unsigned int));
	else if (c == 'x')
		*len += ft_hexa(va_arg(ap, unsigned int), 1);
	else if (c == 'X')
		*len += ft_hexa(va_arg(ap, unsigned int), 0);
	else if (c == '%')
		*len += ft_putchar('%');
	else
		*len += ft_putchar(c);
}
