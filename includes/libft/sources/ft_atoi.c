/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 09:41:03 by nmattos-          #+#    #+#             */
/*   Updated: 2024/11/29 12:39:45 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_atoi(const char *nptr, int *error)
{
	long int	sum;
	int			sign;

	sum = 0;
	sign = 1;
	*error = 1;
	if ((*nptr >= '\t' && *nptr <= '\r') || *nptr == ' ')
		return (0);
	if (*nptr == '+' || *nptr == '-')
		if (*(nptr++) == '-')
			sign *= -1;
	while (*nptr >= '0' && *nptr <= '9' && sum < 2147483648)
		sum = (sum * 10) + (*(nptr++) - 48);
	if (sign == -1)
		if (sum > 2147483648)
			return (0);
	if (sign != -1)
		if (sum > 2147483647)
			return (0);
	if (*nptr != '\0')
		return (0);
	*error = 0;
	return (sum * sign);
}
