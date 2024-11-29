/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 12:55:12 by nmattos-          #+#    #+#             */
/*   Updated: 2024/10/21 14:54:37 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static void	print_argument(t_flags *flags, char *format, va_list ap)
{
	if (*format == '%')
	{
		ft_putchar_fd('%', 1);
		flags->printed += 1;
	}
	else if (*format == 'd' || *format == 'i')
		print_decimal(flags, va_arg(ap, int));
	else if (*format == 's')
		print_string(flags, va_arg(ap, char *));
	else if (*format == 'c')
		print_char(flags, va_arg(ap, int));
	else if (*format == 'u')
		print_unsigned(flags, va_arg(ap, unsigned int));
	else if (*format == 'x' || *format == 'X')
		print_hex(flags, va_arg(ap, unsigned int), *format);
	else if (*format == 'p')
		print_pointer(flags, va_arg(ap, void *));
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	t_flags	*flags;
	char	*specifier;
	int		characters_printed;

	flags = init_flag_struct();
	if (flags == NULL)
		return (-1);
	va_start(ap, str);
	specifier = ft_strchr(str, '%');
	while (specifier != NULL)
	{
		write(1, str, specifier - str);
		flags->printed += specifier - str;
		specifier = get_flags(flags, specifier + 1);
		print_argument(flags, specifier, ap);
		str = specifier + 1;
		specifier = ft_strchr(str, '%');
		reset_flags(flags);
	}
	flags->printed += write(1, str, ft_strlen(str));
	characters_printed = flags->printed;
	free(flags);
	va_end(ap);
	return (characters_printed);
}
