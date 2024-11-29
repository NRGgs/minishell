/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:07:38 by nmattos-          #+#    #+#             */
/*   Updated: 2024/10/21 14:54:56 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static int	get_number_length(t_flags *flags, uintptr_t n)
{
	int				length;

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
	while (n != 0)
	{
		n /= 16;
		length += 1;
	}
	return (length);
}

static void	print_pointer_adress(t_flags *flags, uintptr_t arg)
{
	char	c;

	if (arg < 16)
	{
		if (arg < 10)
			c = arg + 48;
		else
			c = 'a' + (arg - 10);
		ft_putchar_fd(c, 1);
		flags->printed += 1;
		return ;
	}
	print_pointer_adress(flags, arg / 16);
	print_pointer_adress(flags, arg % 16);
}

void	print_pointer(t_flags *flags, void *arg)
{
	int	length;

	if (arg == NULL)
	{
		if (flags->minus == 0)
			add_spaces(flags, flags->fieldwidth - 5);
		ft_putstr_fd("(nil)", 1);
		flags->printed += 5;
		if (flags->minus > 0)
			add_spaces(flags, flags->fieldwidth - 5);
		return ;
	}
	length = get_number_length(flags, (uintptr_t)arg);
	if (flags->minus == 0)
		add_spaces(flags, flags->fieldwidth - (length + 2));
	ft_putstr_fd("0x", 1);
	flags->printed += 2;
	print_pointer_adress(flags, (uintptr_t)arg);
	if (flags->minus > 0)
		add_spaces(flags, flags->fieldwidth - (length + 2));
}
