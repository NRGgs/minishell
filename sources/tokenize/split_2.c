/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:15:16 by nmattos-          #+#    #+#             */
/*   Updated: 2025/02/18 15:26:55 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_word_count(char *s)
{
	int		word_count;
	bool	escaped;

	escaped = false;
	word_count = 0;
	if (*s == '\0')
		return (0);
	skip_spaces(&s);
	while (*s != '\0')
	{
		if (*s == ' ')
		{
			word_count++;
			skip_spaces(&s);
			s--;
		}
		else if ((*s == '\'' || *s == '\"') && escaped == false)
			parse_quote(&s);
		else
			update_escape(&escaped, *s);
		s++;
	}
	if (*(s - 1) != ' ')
		word_count++;
	return (word_count);
}

char	**allocate_words(char *s, char **result)
{
	int		length;
	int		nth_word;
	bool	escaped;

	nth_word = 0;
	length = 0;
	escaped = false;
	skip_spaces(&s);
	while (*s != '\0')
	{
		while (*s != '\0' && *s != ' ')
		{
			if ((*s == '\'' || *s == '\"') && escaped == false)
				length += parse_quote(&s);
			else
				check_escapes(&escaped, &s, &length);
			length++;
			s++;
		}
		if (length > 0)
			if (allocate_next_word(&nth_word, &length, result) == FAIL)
				return (NULL);
		skip_spaces(&s);
	}
	return (result);
}

char	**split_words(char *s, char **result)
{
	int		nth_word;
	bool	escaped;
	int		i;

	nth_word = 0;
	escaped = false;
	skip_spaces(&s);
	while (*s != '\0')
	{
		i = 0;
		while (*s != '\0' && *s != ' ')
		{
			if ((*s == '\'' || *s == '\"') && escaped == false)
				parse_quoted_string(&s, result[nth_word], &i);
			else
			{
				update_escape(&escaped, *s);
				result[nth_word][i++] = *(s++);
			}
		}
		result[nth_word++][i] = '\0';
		skip_spaces(&s);
	}
	result[nth_word] = NULL;
	return (result);
}
