/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 11:16:34 by nmattos           #+#    #+#             */
/*   Updated: 2025/01/28 13:11:08 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strndup(const char *s, size_t len)
{
	char	*dupe;
	size_t	i;

	dupe = malloc((len + 1) * sizeof(char));
	if (dupe == NULL)
		return (NULL);
	i = 0;
	while (i < len && *s)
		dupe[i++] = *(s++);
	dupe[i] = '\0';
	return (dupe);
}
