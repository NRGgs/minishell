/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:48:55 by nmattos-          #+#    #+#             */
/*   Updated: 2025/02/21 16:20:53 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Updates the quotes status.
 *
 * @param c			The character to check.
 * @param new_str	The new string.
 * @param j			The index of the new string.
 * @param in_quotes	The quotes status.
 * @return 			SUCCESS or FAIL.
 */
int	update_quotes(char c, char **new_str, int *j, int *in_quotes)
{
	if (c == '\'')
	{
		if (*in_quotes == FALSE)
			*in_quotes = SINGLE;
		else if (*in_quotes == SINGLE)
			*in_quotes = FALSE;
		else if (*in_quotes == DOUBLE)
			(*new_str)[(*j)++] = c;
		return (SUCCESS);
	}
	else if (c == '\"')
	{
		if (*in_quotes == FALSE)
			*in_quotes = DOUBLE;
		else if (*in_quotes == DOUBLE)
			*in_quotes = FALSE;
		else if (*in_quotes == SINGLE)
			(*new_str)[(*j)++] = c;
		return (SUCCESS);
	}
	return (FAIL);
}

/**
 * @brief Handles backslashes for the quote handler.
 *
 * @param str	The argument to prepare.
 * @return 		SUCCESS or FAIL.
 */
bool	quote_backslash_handler(char **str, char **new_str, int *i, int *j)
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
	if ((*str)[*i] == '\'' || (*str)[*i] == '\"')
		consecutive_backslashes /= 2;
	while (consecutive_backslashes-- > 0)
		(*new_str)[(*j)++] = '\\';
	consecutive_backslashes = 0;
	return (escaped);
}
