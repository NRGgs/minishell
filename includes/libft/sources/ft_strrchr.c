/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 08:16:45 by nmattos-          #+#    #+#             */
/*   Updated: 2024/10/10 12:52:18 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*a;

	a = NULL;
	c %= 256;
	while (*s != '\0')
	{
		if (*s == c)
			a = (char *)s;
		s++;
	}
	if (c == 0)
		return ((char *)s);
	if (a == NULL)
		return (NULL);
	return (a);
}
