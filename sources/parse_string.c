/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:01:21 by nmattos-          #+#    #+#             */
/*   Updated: 2025/02/03 14:14:48 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	parse_string_helper(char *first, char *second, char **pattern);
static bool	air_quote_exists(char **input, int j);
static int	find_quote(char **input, int *i, char **pattern);
static int	receive_input_till_quotes(char **input, int *i, char **pattern);

int	parse_string(char **input, int *i, char **pattern)
{
	int		j;
	char	*first;
	char	*second;

	j = *i;
	first = ft_strchr(input[j], '\"');
	second = ft_strchr(first + 1, '\"');
	if (first != second && second != NULL)
		if (parse_string_helper(first, second, pattern) == FAIL)
			return (FAIL);
	if (second == NULL)
	{
		if (air_quote_exists(input, (*i) + 1))
		{
			if (find_quote(input, i, pattern) == FAIL)
				return (FAIL);
		}
		else
		{
			if (receive_input_till_quotes(input, i, pattern) == FAIL)
				return (FAIL);
		}
	}
	return (SUCCESS);
}

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

static bool	air_quote_exists(char **input, int j)
{
	while (input[j] != NULL)
	{
		if (ft_strchr(input[j], '\"') != NULL)
			return (true);
		j++;
	}
	return (false);
}

static int	find_quote(char **input, int *i, char **pattern)
{
	int		j;
	size_t	size;

	j = *i;
	size = ft_strlen(ft_strchr(input[j], '\"') + 1);
	size += n_chars_till_quote(input, *i + 1) + 1;
	*pattern = ft_calloc((size), sizeof(char));
	if (*pattern == NULL)
		return (FAIL);
	ft_strlcpy(*pattern, ft_strchr(input[j], '\"') + 1, size);
	(*i)++;
	while (input[*i] != NULL)
	{
		if (ft_strchr(input[*i], '\"') != NULL)
		{
			space_strlcat(*pattern, input[*i], size);
			break ;
		}
		space_strlcat(*pattern, input[*i], size);
		(*i)++;
	}
	return (SUCCESS);
}

static int	receive_input_till_quotes(char **input, int *i, char **pattern)
{
	*pattern = ft_strdup(ft_strchr(input[*i], '\"') + 1);
	if (*pattern == NULL)
		return (FAIL);
	if (read_till_quotes("\"", pattern) == NULL)
		return (FAIL);
	return (SUCCESS);
}
