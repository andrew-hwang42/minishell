/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahwang <ahwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 14:17:12 by ahwang            #+#    #+#             */
/*   Updated: 2025/01/05 15:07:36 by ahwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t n, size_t size)
{
	void	*mem;
	size_t	malloc_size;

	mem = NULL;
	malloc_size = n * size;
	if (n && ((malloc_size / n) != size))
		return (NULL);
	mem = (void *)malloc(n * size);
	if (mem == NULL)
		return (NULL);
	ft_bzero(mem, n * size);
	return (mem);
}
