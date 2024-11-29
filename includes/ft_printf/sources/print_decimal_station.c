/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_decimal_station.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 09:42:04 by nmattos-          #+#    #+#             */
/*   Updated: 2024/10/21 14:54:45 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static int	get_number_length(int n)
{
	int		length;

	if (n == 0)
		return (1);
	length = 0;
	while (n != 0)
	{
		n /= 10;
		length += 1;
	}
	return (length);
}

void	print_decimal(t_flags *flags, int n)
{
	int	length;

	length = get_number_length(n);
	if (flags->precision == 0 && n == 0)
	{
		add_spaces(flags, flags->fieldwidth);
		return ;
	}
	if (flags->precision != -1 && flags->minus == 0)
		d_print_precision_right(flags, n, length);
	else if (flags->precision != -1 && flags->minus == 1)
		d_print_precision_left(flags, n, length);
	else if (flags->zero == 1 && flags->minus == 0)
		d_print_zero_right(flags, n, length);
	else if (flags->minus == 1)
		d_print_left(flags, n, length);
	else
		d_print_number(flags, n, length);
}
