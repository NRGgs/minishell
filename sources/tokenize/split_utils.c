/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:17:35 by nmattos-          #+#    #+#             */
/*   Updated: 2025/02/18 15:27:07 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	parse_quote(char **s)
{
	char	quote;
	int		length;

	length = 1;
	quote = **s;
	(*s)++;
	while (**s != '\0')
	{
		if (**s == quote)
			return (length);
		(*s)++;
		length++;
	}
	return (length);
}

void	parse_quoted_string(char **s, char *result, int *i)
{
	bool	in_quotes;
	char	quote;

	in_quotes = true;
	quote = **s;
	result[(*i)++] = **s;
	(*s)++;
	while (**s != '\0' && in_quotes)
	{
		if (**s == quote)
			in_quotes = false;
		result[(*i)++] = **s;
		(*s)++;
	}
	return ;
}

int	allocate_next_word(int *nth_word, int *length, char **result)
{
	result[*nth_word] = malloc((*length + 1) * sizeof(char));
	if (result[*nth_word] == NULL)
	{
		while (nth_word >= 0)
			free(result[(*nth_word)--]);
		free(result);
		return (FAIL);
	}
	*length = 0;
	(*nth_word)++;
	return (SUCCESS);
}
