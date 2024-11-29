/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:14:02 by nmattos-          #+#    #+#             */
/*   Updated: 2024/10/21 14:55:02 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	u_print_precision_right(t_flags *flags, int n, int length)
{
	if (flags->precision < length)
		flags->precision = length;
	add_spaces(flags, flags->fieldwidth - flags->precision);
	add_zeros(flags, flags->precision - length);
	u_putnbr(flags, n);
}

void	u_print_precision_left(t_flags *flags, int n, int length)
{
	if (flags->precision < length)
		flags->precision = length;
	add_zeros(flags, flags->precision - length);
	u_putnbr(flags, n);
	add_spaces(flags, flags->fieldwidth - flags->precision);
}

void	u_print_zero_right(t_flags *flags, int n, int length)
{
	add_zeros(flags, flags->fieldwidth - length);
	u_putnbr(flags, n);
}

void	u_print_left(t_flags *flags, int n, int length)
{
	u_putnbr(flags, n);
	add_spaces(flags, flags->fieldwidth - length);
}

void	u_print_number(t_flags *flags, int n, int length)
{
	add_spaces(flags, flags->fieldwidth - length);
	u_putnbr(flags, n);
}
