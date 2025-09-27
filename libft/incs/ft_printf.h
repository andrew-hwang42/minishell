/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahwang <ahwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 06:04:08 by ahwang            #+#    #+#             */
/*   Updated: 2025/03/04 06:21:57 by ahwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

int		ft_putchar(char c);
int		ft_putstr(char *s);
int		ft_putnbr(int nb);
int		ft_unsigned_int(unsigned int nb);
int		ft_hexa(unsigned long nb, int sign);
int		ft_pointer(unsigned long nb);
void	check_args(char c, va_list ap, int *len);
int		ft_printf(const char *format, ...);

#endif
