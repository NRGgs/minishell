/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 12:48:48 by nmattos           #+#    #+#             */
/*   Updated: 2025/02/14 13:40:19 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strreplace(char *str, char *to_replace, \
		char *replacement, char *location)
{
	char	*new_str;
	char	*start;
	size_t	new_size;

	start = location;
	new_size = ft_strlen(str) - ft_strlen(to_replace) + ft_strlen(replacement);
	new_str = malloc(sizeof(char) * (new_size + 1));
	if (new_str == NULL)
		return (free(str), NULL);
	ft_strlcpy(new_str, str, start - str + 1);
	ft_strlcat(new_str, replacement, new_size + 1);
	ft_strlcat(new_str, start + ft_strlen(to_replace), new_size + 1);
	free(str);
	return (new_str);
}
