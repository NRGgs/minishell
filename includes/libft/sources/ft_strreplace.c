/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strreplace.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmattos <nmattos@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/01 12:48:48 by nmattos       #+#    #+#                 */
/*   Updated: 2024/12/01 13:11:39 by nmattos       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strreplace(char *str, char *to_replace, char *replacement)
{
	char	*new_str;
	char	*start;
	size_t	new_size;

	start = ft_strstr(str, to_replace);
	if (start == NULL)
		return (str);
	new_size = ft_strlen(str) - ft_strlen(to_replace) + ft_strlen(replacement);
	new_str = malloc(sizeof(char) * (new_size + 1));
	if (new_str == NULL)
		return (NULL);
	ft_memcpy(new_str, str, start - str);
	ft_strlcat(new_str, replacement, new_size);
	ft_strlcat(new_str, start + ft_strlen(to_replace), new_size + 1);
	return (new_str);
}
