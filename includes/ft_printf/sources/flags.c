/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:40:15 by nmattos-          #+#    #+#             */
/*   Updated: 2024/10/22 09:53:54 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

t_flags	*init_flag_struct(void)
{
	t_flags	*flags;

	flags = malloc(sizeof(t_flags));
	if (flags == NULL)
		return (NULL);
	flags->minus = 0;
	flags->zero = 0;
	flags->precision = -1;
	flags->alternate = 0;
	flags->space = 0;
	flags->sign = 0;
	flags->fieldwidth = 0;
	flags->printed = 0;
	return (flags);
}

static int	mini_atoi(char **c)
{
	int	sum;

	sum = 0;
	while (**c >= '0' && **c <= '9')
		sum = (sum * 10) + (*(*c)++ - '0');
	return (sum);
}

static bool	is_flag(t_flags *flags, char **c)
{
	if (**c == '-')
		flags->minus = 1;
	else if (**c == '0')
		flags->zero = 1;
	else if (**c == '.')
	{
		*c += 1;
		flags->precision = mini_atoi(c);
		*c -= 1;
	}
	else if (**c == '#')
		flags->alternate = 1;
	else if (**c == ' ')
		flags->space = 1;
	else if (**c == '+')
		flags->sign = 1;
	else if (**c >= '0' && **c <= '9')
	{
		flags->fieldwidth = mini_atoi(c);
		*c -= 1;
	}
	else
		return (false);
	return (true);
}

char	*get_flags(t_flags *flags, char *format)
{
	while (is_flag(flags, &format))
		format++;
	return (format);
}

void	reset_flags(t_flags *flags)
{
	flags->minus = 0;
	flags->zero = 0;
	flags->precision = -1;
	flags->alternate = 0;
	flags->space = 0;
	flags->sign = 0;
	flags->fieldwidth = 0;
}
