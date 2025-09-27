/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahwang <ahwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 14:20:29 by ahwang            #+#    #+#             */
/*   Updated: 2025/01/05 14:20:29 by ahwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *src, const char *find, size_t length)
{
	size_t	i;
	size_t	j;

	if (find[0] == 0)
		return ((char *)src);
	i = 0;
	while (src[i] && i < length)
	{
		j = 0;
		while (src[i + j] == find[j] && i + j < length)
		{
			j++;
			if (find[j] == 0)
				return ((char *)src + i);
		}
		i++;
	}
	return (0);
}
