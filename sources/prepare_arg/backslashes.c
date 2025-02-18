/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backslashes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:48:34 by nmattos-          #+#    #+#             */
/*   Updated: 2025/02/18 10:58:24 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Checks for quotes in the argument.
 *
 * @param c			The character to check.
 * @param in_quotes	Whether we're in a quote or not.
 * @param escaped	The escape status.
 * @return 			True if the character is a quote, false otherwise.
 */
bool	check_quotes(char c, int *in_quotes, bool *escaped)
{
	if (c == '\'' && *in_quotes != DOUBLE)
	{
		if (*escaped == false)
		{
			if (*in_quotes == SINGLE)
				*in_quotes = FALSE;
			else
				*in_quotes = SINGLE;
		}
		else if (*escaped == true && *in_quotes == SINGLE)
			*in_quotes = FALSE;
		*escaped = false;
		return (true);
	}
	else if (c == '\"' && *in_quotes != SINGLE && *escaped == false)
	{
		if (*in_quotes == DOUBLE)
			*in_quotes = FALSE;
		else
			*in_quotes = DOUBLE;
		return (true);
	}
	return (false);
}

/**
 * @brief Handles backslashes in the argument.
 *
 * @param str	The argument to prepare.
 * @return 		SUCCESS or FAIL.
 */
bool	back_backslash_handler(char **str, char **new_str, int *i, int *j)
{
	size_t	consecutive_backslashes;
	bool	escaped;

	escaped = false;
	consecutive_backslashes = 0;
	while ((*str)[*i] == '\\')
	{
		consecutive_backslashes++;
		(*i)++;
	}
	if (consecutive_backslashes % 2 == 1)
		escaped = true;
	if ((*str)[*i] != '\'' && (*str)[*i] != '\"')
		consecutive_backslashes /= 2;
	while (consecutive_backslashes-- > 0)
		(*new_str)[(*j)++] = '\\';
	consecutive_backslashes = 0;
	return (escaped);
}
