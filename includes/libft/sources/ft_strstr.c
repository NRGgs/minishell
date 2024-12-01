/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strstr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmattos <nmattos@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/01 11:09:25 by nmattos       #+#    #+#                 */
/*   Updated: 2024/12/01 11:10:14 by nmattos       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*compare_little(char *str, char *substr)
{
	char	*found;

	found = str;
	while (*substr != '\0' && *substr == *str)
	{
		substr++;
		str++;
	}
	if (*substr == '\0')
		return (found);
	return (NULL);
}

char	*ft_strstr(const char *big, const char *little)
{
	char	*found;

	if (*little == '\0')
		return ((char *)big);
	found = NULL;
	while (*big != '\0' && found == NULL)
	{
		if (*little == *big)
		{
			found = compare_little((char *)big, (char *)little);
			if (found != NULL)
				return (found);
		}
		big++;
	}
	return (NULL);
}