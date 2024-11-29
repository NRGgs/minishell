/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:03:12 by nmattos-          #+#    #+#             */
/*   Updated: 2024/10/10 14:47:20 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	calc_length(char const *s)
{
	int	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	int		length;

	length = (calc_length(s1) + calc_length(s2));
	if (length == 0)
	{
		result = malloc(1 * sizeof(char));
		if (result == NULL)
			return (NULL);
		*result = '\0';
		return (result);
	}
	result = malloc((length + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	while (*s1 != '\0')
		*(result++) = *(s1++);
	while (*s2 != '\0')
		*(result++) = *(s2++);
	*result = '\0';
	return (result - length);
}
