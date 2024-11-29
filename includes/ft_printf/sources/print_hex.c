/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:10:28 by nmattos-          #+#    #+#             */
/*   Updated: 2024/10/21 14:54:53 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	h_print_precision_right(t_flags *flags, unsigned int n,
									int length, char format)
{
	if (flags->precision < length)
		flags->precision = length;
	if (flags->alternate > 0 && n != 0)
	{
		add_spaces(flags, flags->fieldwidth - flags->precision - 2);
		add_prefix(flags, format);
	}
	else
		add_spaces(flags, flags->fieldwidth - flags->precision);
	add_zeros(flags, flags->precision - length);
	h_putnbr(flags, n, format);
}

void	h_print_precision_left(t_flags *flags, unsigned int n,
									int length, char format)
{
	if (flags->precision < length)
		flags->precision = length;
	if (flags->alternate > 0 && n != 0)
		add_prefix(flags, format);
	add_zeros(flags, flags->precision - length);
	h_putnbr(flags, n, format);
	if (flags->alternate > 0)
		add_spaces(flags, flags->fieldwidth - flags->precision - 2);
	else
		add_spaces(flags, flags->fieldwidth - flags->precision);
}

void	h_print_zero_right(t_flags *flags, unsigned int n,
								int length, char format)
{
	if (flags->alternate > 0 && n != 0)
	{
		add_prefix(flags, format);
		add_zeros(flags, flags->fieldwidth - length - 2);
	}
	else
		add_zeros(flags, flags->fieldwidth - length);
	h_putnbr(flags, n, format);
}

void	h_print_left(t_flags *flags, unsigned int n,
						int length, char format)
{
	if (flags->alternate > 0 && n != 0)
		add_prefix(flags, format);
	h_putnbr(flags, n, format);
	if (flags->alternate > 0)
		add_spaces(flags, flags->fieldwidth - length - 2);
	else
		add_spaces(flags, flags->fieldwidth - length);
}

void	h_print_number(t_flags *flags, unsigned int n,
							int length, char format)
{
	if (flags->alternate > 0)
		add_spaces(flags, flags->fieldwidth - length - 2);
	else
		add_spaces(flags, flags->fieldwidth - length);
	if (flags->alternate > 0 && n != 0)
		add_prefix(flags, format);
	h_putnbr(flags, n, format);
}
