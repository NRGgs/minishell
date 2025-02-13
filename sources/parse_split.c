/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_split.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmattos <nmattos@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/13 13:29:49 by nmattos       #+#    #+#                 */
/*   Updated: 2025/02/13 15:32:38 by nmattos       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	skip_spaces(char **s)
{
	while (**s == ' ')
		(*s)++;
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

static int	get_word_count(char *s)
{
	int	word_count;

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
		}
		else if (*s == '\'' || *s == '\"')
		{
			parse_quote(&s);
			s++;
		}
		else
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
	return ;
}

static char	**allocate_words(char *s, char **result)
{
	int	length;
	int	nth_word;

	nth_word = 0;
	length = 1;
	skip_spaces(&s);
	while (*s != '\0')
	{
		while (*s != '\0' && *s != ' ')
		{
			if (*s == '\'' || *s == '\"')
				length += parse_quote(&s);
			length++;
			s++;
		}
		if (length > 0)
		{
			result[nth_word] = malloc((length) * sizeof(char));
			if (result[nth_word] == NULL)
				return (free_result(result, nth_word - 1), NULL);
			length = 1;
			nth_word++;
		}
		skip_spaces(&s);
	}
	return (result);
}

static char	**split_words(char *s, char **result)
{
	int	nth_word;
	int	i;

	nth_word = 0;
	i = 0;
	skip_spaces(&s);
	while (*s != '\0')
	{
		while (*s != '\0' && *s != ' ')
		{
			if (*s == '\'' || *s == '\"')
				parse_quoted_string(&s, result[nth_word], &i);
			else
				result[nth_word][i++] = *(s++);
		}
		result[nth_word++][i] = '\0';
		i = 0;
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

static char	check_open_quotes(char *str)
{
	bool	in_single;
	bool	in_double;
	int		i;

	in_single = false;
	in_double = false;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && !in_double)
			in_single = !in_single;
		if (str[i] == '\"' && !in_single)
			in_double = !in_double;
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
	quote = check_open_quotes(s);
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

// int	main(void)
// {
// 	int i = 0;
// 	char *unfinished = ft_strdup("Hello World \"This    is  \' a   test");
// 	char **result = parse_split(unfinished);
// 	if (result == NULL)
// 		printf("result is NULL\n");
// 	while (result[i] != NULL)
// 	{
// 		printf("result[%d]: %s\n", i, result[i]);
// 		i++;
// 	}
// 	i = 0;
// 	while (result[i] != NULL)
// 	{
// 		free(result[i]);
// 		i++;
// 	}
// 	free(result);

// 	return (0);
// }
