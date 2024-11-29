/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex_station.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:20:26 by nmattos-          #+#    #+#             */
/*   Updated: 2024/10/21 14:54:50 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static int	get_number_length(t_flags *flags, int n)
{
	int				length;
	unsigned int	n1;

	if (n == 0)
		return (1);
	length = 0;
	if (n < 0)
	{
		length++;
		flags->fieldwidth += 1;
		if (flags->precision > 0)
			flags->precision += 1;
	}
	n1 = (unsigned int)n;
	while (n1 != 0)
	{
		n1 /= 16;
		length += 1;
	}
	return (length);
}

void	print_hex(t_flags *flags, unsigned int n, char format)
{
	int	length;

	length = get_number_length(flags, n);
	if (flags->precision == 0 && n == 0)
	{
		add_spaces(flags, flags->fieldwidth);
		return ;
	}
	if (flags->precision != -1 && flags->minus == 0)
		h_print_precision_right(flags, n, length, format);
	else if (flags->precision != -1 && flags->minus == 1)
		h_print_precision_left(flags, n, length, format);
	else if (flags->zero == 1 && flags->minus == 0)
		h_print_zero_right(flags, n, length, format);
	else if (flags->minus == 1)
		h_print_left(flags, n, length, format);
	else
		h_print_number(flags, n, length, format);
}
