/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 09:14:26 by nmattos-          #+#    #+#             */
/*   Updated: 2025/02/17 09:14:54 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_realloc(char *str, size_t size)
{
	char	*new_str;

	new_str = malloc((size + 1) * sizeof(char));
	if (new_str == NULL)
		return (free(str), NULL);
	ft_strlcpy(new_str, str, size);
	free(str);
	return (new_str);
}
