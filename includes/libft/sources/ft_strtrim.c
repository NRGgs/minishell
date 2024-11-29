/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:26:43 by nmattos-          #+#    #+#             */
/*   Updated: 2024/10/10 17:28:57 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	init_vars(int *start, int *end, char const *s1, char const *set)
{
	*start = 0;
	*end = 0;
	while (ft_strchr(set, s1[*start]) != NULL)
		*start += 1;
	*end = (size_t)ft_strlen(s1);
	while (ft_strchr(set, s1[*end]) != NULL)
		*end -= 1;
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	int		i;
	int		len;
	int		start;
	int		end;

	i = 0;
	init_vars(&start, &end, s1, set);
	len = end - start + 1;
	if (len <= 0)
	{
		result = malloc(1 * sizeof(char));
		if (result == NULL)
			return (NULL);
		*result = '\0';
		return (result);
	}
	result = malloc((len + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	while (i < len)
		result[i++] = s1[start++];
	result[i] = '\0';
	return (result);
}
