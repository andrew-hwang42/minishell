/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahwang <ahwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 14:19:12 by ahwang            #+#    #+#             */
/*   Updated: 2025/01/05 14:19:13 by ahwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t length)
{
	unsigned char	*usrc;
	unsigned char	*udst;

	if (dst == src || length == 0)
		return (dst);
	if (dst < src)
	{
		udst = (unsigned char *)dst;
		usrc = (unsigned char *)src;
		while (length--)
			*udst++ = *usrc++;
	}
	else
	{
		udst = (unsigned char *)dst + (length - 1);
		usrc = (unsigned char *)src + (length - 1);
		while (length--)
			*udst-- = *usrc--;
	}
	return (dst);
}
