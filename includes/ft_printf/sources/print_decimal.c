/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_decimal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:09:06 by nmattos-          #+#    #+#             */
/*   Updated: 2024/10/21 14:54:47 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	d_print_precision_right(t_flags *flags, int n, int length)
{
	if (flags->precision < length)
		flags->precision = length;
	if (n < 0 || flags->space > 0 || flags->sign > 0)
	{
		add_spaces(flags, flags->fieldwidth - flags->precision - 1);
		d_print_sign(flags, n);
	}
	else
		add_spaces(flags, flags->fieldwidth - flags->precision);
	add_zeros(flags, flags->precision - length);
	d_putnbr(flags, n);
}

void	d_print_precision_left(t_flags *flags, int n, int length)
{
	if (flags->precision < length)
		flags->precision = length;
	d_print_sign(flags, n);
	add_zeros(flags, flags->precision - length);
	d_putnbr(flags, n);
	if (n < 0 || flags->space > 0 || flags->sign > 0)
		add_spaces(flags, flags->fieldwidth - flags->precision - 1);
	else
		add_spaces(flags, flags->fieldwidth - flags->precision);
}

void	d_print_zero_right(t_flags *flags, int n, int length)
{
	d_print_sign(flags, n);
	if (n < 0 || flags->space > 0 || flags->sign > 0)
		add_zeros(flags, flags->fieldwidth - length - 1);
	else
		add_zeros(flags, flags->fieldwidth - length);
	d_putnbr(flags, n);
}

void	d_print_left(t_flags *flags, int n, int length)
{
	d_print_sign(flags, n);
	d_putnbr(flags, n);
	if (n < 0 || flags->space > 0 || flags->sign > 0)
		add_spaces(flags, flags->fieldwidth - length - 1);
	else
		add_spaces(flags, flags->fieldwidth - length);
}

void	d_print_number(t_flags *flags, int n, int length)
{
	if (n < 0 || flags->space > 0 || flags->sign > 0)
		add_spaces(flags, flags->fieldwidth - length - 1);
	else
		add_spaces(flags, flags->fieldwidth - length);
	d_print_sign(flags, n);
	d_putnbr(flags, n);
}
