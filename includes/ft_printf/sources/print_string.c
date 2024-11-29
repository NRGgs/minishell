/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 11:47:19 by nmattos-          #+#    #+#             */
/*   Updated: 2024/10/21 14:54:58 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	print_null(t_flags *flags)
{
	if (flags->precision < 6 && flags->precision >= 0)
	{
		if (flags->fieldwidth > 0)
			add_spaces(flags, flags->fieldwidth);
		return ;
	}
	else if (flags->precision >= 6)
	{
		if (flags->minus == 0 && flags->fieldwidth > 6)
			add_spaces(flags, flags->fieldwidth - 6);
		write(1, "(null)", 6);
		flags->printed += 6;
		if (flags->minus > 0)
			add_spaces(flags, flags->fieldwidth - 6);
		return ;
	}
	else if (flags->fieldwidth > 0 && flags->minus == 0)
		add_spaces(flags, flags->fieldwidth - 6);
	write(1, "(null)", 6);
	if (flags->minus > 0)
		add_spaces(flags, flags->fieldwidth - 6);
	flags->printed += 6;
}

void	print_string(t_flags *flags, char *str)
{
	int	length;

	if (str == NULL)
	{
		print_null(flags);
		return ;
	}
	length = ft_strlen(str);
	if (flags->precision >= 0)
		if (flags->precision < length)
			length = flags->precision;
	if (flags->minus == 0)
		add_spaces(flags, flags->fieldwidth - length);
	write(1, str, length);
	flags->printed += length;
	if (flags->minus > 0)
		add_spaces(flags, flags->fieldwidth - length);
}
