/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:38:46 by nmattos-          #+#    #+#             */
/*   Updated: 2024/10/10 14:42:42 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	get_memory_size(size_t s_length, unsigned int start, size_t len)
{
	if (s_length - start < len)
		return (s_length - start);
	else
		return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	s_length;
	size_t	memory;

	if (s == NULL)
	{
		substr = malloc(1);
		*substr = '\0';
		return (substr);
	}
	s_length = ft_strlen(s);
	if (start > s_length)
	{
		substr = malloc(1);
		*substr = '\0';
		return (substr);
	}
	memory = get_memory_size(s_length, start, len);
	substr = malloc((memory + 1) * sizeof(char));
	if (substr == NULL)
		return (NULL);
	ft_strlcpy(substr, s + start, len + 1);
	return (substr);
}
