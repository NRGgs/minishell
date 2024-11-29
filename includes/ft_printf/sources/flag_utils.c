/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:19:06 by nmattos-          #+#    #+#             */
/*   Updated: 2024/10/21 14:54:33 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	add_spaces(t_flags *flags, int spaces)
{
	char	*buffer;

	if (spaces <= 0)
		return ;
	buffer = malloc(500);
	if (buffer == NULL)
		return ;
	ft_memset(buffer, ' ', 500);
	flags->printed += spaces;
	while (spaces >= 500)
	{
		write(1, buffer, 500);
		spaces -= 500;
	}
	if (spaces > 0)
		write(1, buffer, spaces);
	free(buffer);
}

void	add_zeros(t_flags *flags, int zeros)
{
	char	*buffer;

	if (zeros <= 0)
		return ;
	buffer = malloc(500);
	if (buffer == NULL)
		return ;
	ft_memset(buffer, '0', 500);
	flags->printed += zeros;
	while (zeros >= 500)
	{
		write(1, buffer, 500);
		zeros -= 500;
	}
	if (zeros > 0)
		write(1, buffer, zeros);
	free(buffer);
}
