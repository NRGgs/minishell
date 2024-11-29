/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:42:07 by nmattos-          #+#    #+#             */
/*   Updated: 2024/10/10 13:33:08 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	int		j;

	i = 0;
	j = 0;
	if (size > 0)
	{
		while (dst[i] != '\0' && i < size)
			i++;
		while (src[j] != '\0' && i < size - 1)
		{
			dst[i] = src[j];
			i++;
			j++;
		}
		if (j > 0)
			dst[i] = '\0';
	}
	while (src[j++] != '\0')
		i++;
	return (i);
}
