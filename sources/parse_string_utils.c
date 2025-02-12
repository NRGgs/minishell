/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_string_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:03:25 by nmattos-          #+#    #+#             */
/*   Updated: 2025/02/12 13:34:41 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*	Checks whether a string contains single or double air quotes.
 *
 *	str:	The string to check.
 *
 *	Return:	'\"' if the string contains double quotes,
 *			'\'' if the string contains single quotes,
 *			'0' if the string contains no quotes.
 */
char	contains_quote(char *str)
{
	if (ft_strchr(str, '\"') != NULL)
		return ('\"');
	if (ft_strchr(str, '\'') != NULL)
		return ('\'');
	return ('0');
}

/*	Counts the number of characters in a string until a quote is found.
 *
 *	input:	Array of strings.
 *	j:		The index of where to start in the input array.
 *	quote:	The quote to look for (single or double).
 *
 *	Return:	The number of characters until the quote is reached.
 */
int	n_chars_till_quote(char **input, int j, char quote)
{
	int		start;
	int		k;
	size_t	size;

	size = 0;
	start = j - 1;
	while (input[j] != NULL)
	{
		if (ft_strchr(input[j], quote) != NULL)
		{
			k = 0;
			while (input[j][k] != quote)
			{
				size++;
				k++;
			}
			return (size + (j - start));
		}
		size += ft_strlen(input[j]);
		j++;
	}
	return (size);
}

/*	Attaches a buffer to the end of the string.
 *
 *	pattern:	The string to attach the buffer to.
 *	buffer:		The buffer to attach.
 *
 *	Return:		A new string with the buffer attached.
 */
static char	*attach_buffer(char *pattern, char *buffer)
{
	char	*temp;

	pattern = add_newline(pattern);
	if (pattern == NULL)
		return (free(buffer), NULL);
	temp = ft_strjoin(pattern, buffer);
	free(buffer);
	if (temp == NULL)
		return (free(pattern), NULL);
	free(pattern);
	pattern = ft_strdup(temp);
	if (pattern == NULL)
		return (free(temp), NULL);
	free(temp);
	return (pattern);
}

/*	Reads from the terminal until a quote is given by the user.
 *
 *	delimiter:	The quote to look for (single or double).
 *	pattern:	The string to attach the input to.
 *
 *	Return:		The string with the input attached.
 */
char	*read_till_quotes(char delimiter, char **pattern)
{
	char	*buffer;
	bool	reading;

	reading = true;
	while (reading)
	{
		buffer = readline("\\ ");
		if (buffer != NULL && ft_strchr(buffer, delimiter) != NULL)
			reading = false;
		*pattern = attach_buffer(*pattern, buffer);
		if (*pattern == NULL)
			return (NULL);
	}
	return (*pattern);
}
