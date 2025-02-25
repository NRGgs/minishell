/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:14:05 by nmattos-          #+#    #+#             */
/*   Updated: 2025/02/21 16:26:55 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	check_open_quotes(char *str, int i);
static char	**shell_ft_split(char const *s);

char	**parse_split(char *s)
{
	char	**result;
	char	quote;

	if (s == NULL)
		return (NULL);
	quote = check_open_quotes(s, 0);
	if (quote != '0')
	{
		s = read_till_quotes(quote, &s);
		if (s == NULL)
			return (NULL);
	}
	result = shell_ft_split(s);
	free(s);
	return (result);
}

static char	check_open_quotes(char *str, int i)
{
	bool	in_single;
	bool	in_double;
	bool	escaped;

	in_single = false;
	in_double = false;
	escaped = false;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && !in_double && escaped == false)
			in_single = !in_single;
		else if (str[i] == '\"' && !in_single && escaped == false)
			in_double = !in_double;
		else if (!in_single)
			update_escape(&escaped, str[i]);
		i++;
	}
	if (in_single)
		return ('\'');
	if (in_double)
		return ('\"');
	return ('0');
}

static char	**shell_ft_split(char const *s)
{
	char	**result;

	if (s == NULL)
		return (NULL);
	result = malloc((get_word_count((char *)s) + 1) * sizeof(char *));
	if (result == NULL)
		return (NULL);
	if (get_word_count((char *)s) == 0)
	{
		result[0] = NULL;
		return (result);
	}
	result = allocate_words((char *)s, result);
	if (result == NULL)
		return (NULL);
	result = split_words((char *)s, result);
	return (result);
}
