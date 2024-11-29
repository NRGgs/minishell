/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:02:05 by nmattos-          #+#    #+#             */
/*   Updated: 2024/11/29 12:39:37 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*allocate_string(int n, size_t *length)
{
	char	*str;

	if (n < 0)
	{
		*length += 1;
		n *= -1;
	}
	if (n == 0)
		*length = 1;
	while (n != 0)
	{
		n /= 10;
		*length += 1;
	}
	str = malloc((*length + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	*(str + *length) = '\0';
	return (str);
}

static void	calculate(char *str, long n)
{
	if (n < 10)
	{
		*str = n + 48;
		return ;
	}
	calculate(str - 1, n / 10);
	calculate(str, n % 10);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	big_n;
	size_t	length;

	length = 0;
	big_n = n;
	str = allocate_string(n, &length);
	if (str == NULL)
		return (NULL);
	if (big_n < 0)
	{
		big_n *= -1;
		*str = '-';
	}
	calculate(str + length - 1, big_n);
	return (str);
}
