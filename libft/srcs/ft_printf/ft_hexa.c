/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahwang <ahwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 06:04:06 by ahwang            #+#    #+#             */
/*   Updated: 2025/03/04 06:04:07 by ahwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_hexa(unsigned long nb, int sign)
{
	int	len;

	len = 0;
	if (nb >= 16)
		len += ft_hexa(nb / 16, sign);
	if (nb % 16 < 10)
		len += ft_putchar((nb % 16) + 48);
	else
	{
		if (sign == 1)
			len += ft_putchar((nb % 16) + 87);
		else
			len += ft_putchar((nb % 16) + 55);
	}
	return (len);
}
