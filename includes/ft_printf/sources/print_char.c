/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:15:33 by nmattos-          #+#    #+#             */
/*   Updated: 2024/10/21 14:54:43 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	print_char(t_flags *flags, int c)
{
	if (flags->minus == 0)
		add_spaces(flags, flags->fieldwidth - 1);
	ft_putchar_fd(c, 1);
	flags->printed += 1;
	if (flags->minus)
		add_spaces(flags, flags->fieldwidth - 1);
}
