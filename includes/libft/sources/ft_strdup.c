/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 10:50:10 by nmattos-          #+#    #+#             */
/*   Updated: 2024/10/10 14:08:00 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*dupe;

	len = 0;
	while (*(s++) != '\0')
		len++;
	dupe = malloc((len + 1) * sizeof(char));
	if (dupe == NULL)
		return (NULL);
	s--;
	while (len > 0)
		dupe[len--] = *(s--);
	dupe[len] = *(s);
	return (dupe);
}
