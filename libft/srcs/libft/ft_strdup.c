/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahwang <ahwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 14:19:55 by ahwang            #+#    #+#             */
/*   Updated: 2025/01/05 14:19:56 by ahwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*dup;
	size_t	len;

	len = 0;
	while (src[len])
		len++;
	dup = (char *)malloc(len + 1);
	if (!(dup))
		return (NULL);
	ft_memcpy(dup, src, len);
	dup[len] = 0;
	return (dup);
}
