/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:26:50 by nmattos-          #+#    #+#             */
/*   Updated: 2024/10/21 14:55:04 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	d_putnbr(t_flags *flags, int n)
{
	char	c;

	if (n == -2147483648)
	{
		write(1, "2147483648", 10);
		flags->printed += 10;
		return ;
	}
	if (n < 0)
	{
		d_putnbr(flags, -n);
		return ;
	}
	if (n < 10)
	{
		c = n + 48;
		write(1, &c, 1);
		flags->printed += 1;
		return ;
	}
	d_putnbr(flags, n / 10);
	d_putnbr(flags, n % 10);
}

void	u_putnbr(t_flags *flags, unsigned int n)
{
	char	c;

	if (n < 10)
	{
		c = n + 48;
		write(1, &c, 1);
		flags->printed += 1;
		return ;
	}
	u_putnbr(flags, n / 10);
	u_putnbr(flags, n % 10);
}

void	h_putnbr(t_flags *flags, unsigned int arg, char format)
{
	char	c;

	if (arg < 16)
	{
		if (arg < 10)
			c = arg + 48;
		else if (format == 'X')
			c = 'A' + (arg - 10);
		else
			c = 'a' + (arg - 10);
		ft_putchar_fd(c, 1);
		flags->printed += 1;
		return ;
	}
	h_putnbr(flags, arg / 16, format);
	h_putnbr(flags, arg % 16, format);
}

void	add_prefix(t_flags *flags, char format)
{
	ft_putchar_fd('0', 1);
	ft_putchar_fd(format, 1);
	flags->printed += 2;
}

void	d_print_sign(t_flags *flags, int n)
{
	if (n < 0)
	{
		write(1, "-", 1);
		flags->printed++;
	}
	else if (flags->sign > 0)
	{
		write(1, "+", 1);
		flags->printed++;
	}
	else if (flags->space > 0)
	{
		write(1, " ", 1);
		flags->printed++;
	}
}
