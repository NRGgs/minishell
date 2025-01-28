/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 11:09:25 by nmattos           #+#    #+#             */
/*   Updated: 2025/01/28 13:11:28 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*compare_little(char *str, char *substr)
{
	char	*found;

	found = str;
	while (*substr != '\0' && *substr == *str)
	{
		substr++;
		str++;
	}
	if (*substr == '\0')
		return (found);
	return (NULL);
}

char	*ft_strstr(const char *big, const char *little)
{
	char	*found;

	if (*little == '\0')
		return ((char *)big);
	found = NULL;
	while (*big != '\0' && found == NULL)
	{
		if (*little == *big)
		{
			found = compare_little((char *)big, (char *)little);
			if (found != NULL)
				return (found);
		}
		big++;
	}
	return (NULL);
}
