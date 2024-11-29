/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 08:50:01 by nmattos-          #+#    #+#             */
/*   Updated: 2024/10/10 10:56:08 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*compare_little(char *str, char *substr, size_t len)
{
	char	*found;

	found = str;
	while (*substr == *str && len-- > 0)
	{
		substr++;
		str++;
	}
	if (*substr == '\0')
		return (found);
	return (NULL);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*found;

	if (*little == '\0')
		return ((char *)big);
	found = NULL;
	while (*big != '\0' && len > 0 && found == NULL)
	{
		if (*little == *big)
		{
			found = compare_little((char *)big, (char *)little, len);
			if (found != NULL)
				return (found);
		}
		big++;
		len--;
	}
	return (NULL);
}
