/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strndup.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmattos <nmattos@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/01 11:16:34 by nmattos       #+#    #+#                 */
/*   Updated: 2024/12/01 11:42:40 by nmattos       ########   odam.nl         */
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