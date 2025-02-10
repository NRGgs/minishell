/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:01:21 by nmattos-          #+#    #+#             */
/*   Updated: 2025/02/10 11:58:02 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	parse_string_helper(char *first, char *second, char **pattern);
static bool	air_quote_exists(char **input, int j, char quote);
static int	find_quote(char **input, int *i, char **pattern, char quote);
static int	receive_input_till_quotes(char **input, int *i, \
		char **pattern, char quote);

/*	Parses the string between the quotes.
 *
 *	input:		An array of strings.
 *	i:			The index of the first string.
 *	pattern:	The pattern to store the input.
 *	quote:		The quote to look for.
 *
 *	Return:		SUCCESS or FAIL.
 */
int	parse_string(char **input, int *i, char **pattern, char quote)
{
	int		j;
	char	*first;
	char	*second;

	j = *i;
	first = ft_strchr(input[j], quote);
	second = ft_strchr(first + 1, quote);
	if (first != second && second != NULL)
		if (parse_string_helper(first, second, pattern) == FAIL)
			return (FAIL);
	if (second == NULL)
	{
		if (air_quote_exists(input, (*i) + 1, quote))
		{
			if (find_quote(input, i, pattern, quote) == FAIL)
				return (FAIL);
		}
		else
		{
			if (receive_input_till_quotes(input, i, pattern, quote) == FAIL)
				return (FAIL);
		}
	}
	return (SUCCESS);
}

/*	Parses the string between the quotes.
 *
 *	first:		The first quote.
 *	second:		The second quote.
 *	pattern:	The pattern to store the input.
 *
 *	Return:		SUCCESS or FAIL.
 */
static int	parse_string_helper(char *first, char *second, char **pattern)
{
	size_t	size;

	size = second - first;
	*pattern = ft_calloc((size + 1), sizeof(char));
	if (*pattern == NULL)
		return (FAIL);
	ft_strlcpy(*pattern, first + 1, size);
	return (SUCCESS);
}

/*	Checks if a quote exists in the input.
 *
 *	input:	An array of strings.
 *	j:		The index of where to start in the input array.
 *	quote:	The quote to look for (single or double).
 *
 *	Return:	true if the quote exists, false if it does not.
 */
static bool	air_quote_exists(char **input, int j, char quote)
{
	while (input[j] != NULL)
	{
		if (ft_strchr(input[j], quote) != NULL)
			return (true);
		j++;
	}
	return (false);
}

/*	Creates a string to store the input until the quote is found.
 *
 *	input:		An array of strings.
 *	i:			The index of the first string.
 *	pattern:	The pattern to store the input.
 *	quote:		The quote to look for.
 *
 *	Return:		SUCCESS or FAIL.
 */
static int	find_quote(char **input, int *i, char **pattern, char quote)
{
	int		j;
	size_t	size;

	j = *i;
	size = ft_strlen(ft_strchr(input[j], quote) + 1);
	size += n_chars_till_quote(input, *i + 1, quote);
	*pattern = malloc((size + 1) * sizeof(char));
	if (*pattern == NULL)
		return (FAIL);
	ft_strlcpy(*pattern, ft_strchr(input[j], quote) + 1, size + 1);
	(*i)++;
	while (input[*i] != NULL)
	{
		if (ft_strchr(input[*i], quote) != NULL)
		{
			space_strlcat(*pattern, input[*i], size + 1);
			break ;
		}
		space_strlcat(*pattern, input[*i], size + 1);
		(*i)++;
	}
	return (SUCCESS);
}

/*	Receives input until the closing quote.
 *
 *	input:		An array of strings.
 *	i:			The index of the first string.
 *	pattern:	The pattern to store the input.
 *	quote:		The quote to look for.
 *
 *	Return:		SUCCESS or FAIL.
 */
static int	receive_input_till_quotes(char **input, int *i, \
		char **pattern, char quote)
{
	size_t	size;
	int		j;

	j = *i;
	size = ft_strlen(input[j]);
	j++;
	while (input[j] != NULL)
	{
		size++;
		size += ft_strlen(input[j]);
		j++;
	}
	*pattern = malloc(sizeof(char) * size + 1);
	if (*pattern == NULL)
		return (FAIL);
	ft_strlcpy(*pattern, input[*i] + 1, size + 1);
	(*i)++;
	while (input[*i] != NULL)
		space_strlcat(*pattern, input[(*i)++], size + 1);
	(*i)--;
	if (read_till_quotes(quote, pattern) == NULL)
		return (FAIL);
	return (SUCCESS);
}
