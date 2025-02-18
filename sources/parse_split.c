/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:29:49 by nmattos           #+#    #+#             */
/*   Updated: 2025/02/18 12:56:43 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	skip_spaces(char **s)
{
	while (**s == ' ')
		(*s)++;
}

static int	is_escaped(char **s)
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

static int	parse_quote(char **s)
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

static void	parse_quoted_string(char **s, char *result, int *i)
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

static void	update_escape(bool *escaped, char c)
{
	if (c == '\\')
		*escaped = !*escaped;
	if (c != '\\')
		*escaped = false;
}

static int	get_word_count(char *s)
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

static void	free_result(char **result, int nth_word)
{
	while (nth_word >= 0)
		free(result[nth_word++]);
	free(result);
}

static void	check_escapes(bool *escaped, char **s, int *length)
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

static int	allocate_next_word(int *nth_word, int *length, char **result)
{
	result[*nth_word] = malloc((*length + 1) * sizeof(char));
	if (result[*nth_word] == NULL)
		return (free_result(result, *nth_word - 1), FAIL);
	*length = 0;
	(*nth_word)++;
	return (SUCCESS);
}

static char	**allocate_words(char *s, char **result)
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

static char	**split_words(char *s, char **result)
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
		else if (str[i] == '\\')
			escaped = !escaped;
		else
			escaped = false;
		i++;
	}
	if (in_single)
		return ('\'');
	if (in_double)
		return ('\"');
	return ('0');
}

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
