/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmattos <nmattos@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/01 10:44:05 by nmattos       #+#    #+#                 */
/*   Updated: 2024/12/01 11:48:27 by nmattos       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parse.h"

/*	Check if the string is a variable.
 *
 *	str: the string to be checked.
 *
 *	Return: true / false.
 */
bool	is_variable(char *str)
{
	if (ft_strstr(str, "=\"") == NULL)
		return (false);
	return (true);
}

/*	Parse the variable from the string.
 *
 *	str: the string to be parsed.
 *
 * 	Return: NULL terminated **array.
 * 			NULL if malloc fails.
 */
char	**parse_variable(char *str)
{
	char	**variable;
	size_t	len;

	variable = malloc(sizeof(char *) * 3);
	if (variable == NULL)
		return (NULL);
	len = ft_strchr(str, '=') - str;
	variable[0] = ft_strndup(str, len);
	if (variable[0] == NULL)
	{
		free(variable);
		return (NULL);
	}
	len = (ft_strrchr(str, '"')) - (ft_strchr(str, '"') + 1);
	variable[1] = ft_strndup(ft_strchr(str, '"') + 1, len);
	if (variable[1] == NULL)
	{
		free(variable[0]);
		free(variable);
		return (NULL);
	}
	variable[2] = NULL;
	return (variable);
}
