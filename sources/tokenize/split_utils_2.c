/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   split_utils_2.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmattos- <nmattos-@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/18 15:16:56 by nmattos-      #+#    #+#                 */
/*   Updated: 2025/02/25 12:19:31 by nmattos       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	skip_spaces(char **s)
// {
// 	while (**s == ' ')
// 		(*s)++;
// }

int	is_escaped(char **s)
{
	int	escaped;

	escaped = 0;
	while (**s == '\\')
	{
		escaped++;
		(*s)++;
	}
	return (escaped);
}

void	update_escape(bool *escaped, char c)
{
	if (c == '\\')
		*escaped = !*escaped;
	if (c != '\\')
		*escaped = false;
}

void	check_escapes(bool *escaped, char **s, int *length)
{
	int	backslashes;

	if (**s == '\\')
	{
		backslashes = is_escaped(s);
		length += (backslashes) - 1;
		if (backslashes % 2 == 1)
			*escaped = true;
		(*s)--;
	}
	else
		*escaped = false;
}
