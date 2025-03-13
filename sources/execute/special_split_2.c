/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_split_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:57:30 by iriadyns          #+#    #+#             */
/*   Updated: 2025/03/13 16:07:02 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*allocate_token(const char *s, int start, int len)
{
	char	*token;
	int		j;

	token = malloc(len + 1);
	if (!token)
		return (NULL);
	j = 0;
	while (j < len)
	{
		token[j] = s[start + j];
		j++;
	}
	token[j] = '\0';
	return (token);
}

static void	free_tokens(char **tokens, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

static int	skip_delimiters(const char *s, char c, int i)
{
	while (s[i] && (s[i] == c || s[i] == '\001'))
		i++;
	return (i);
}

static int	read_token_length(const char *s, char c, int i)
{
	int	start;

	start = i;
	while (s[i] && s[i] != c && s[i] != '\001')
		i++;
	return (i - start);
}

char	**fill_tokens(const char *s, char c, int token_count)
{
	char	**result;
	int		i;
	int		word;
	int		token_len;

	result = malloc((token_count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	word = 0;
	while (s[i])
	{
		i = skip_delimiters(s, c, i);
		if (s[i])
		{
			token_len = read_token_length(s, c, i);
			result[word] = allocate_token(s, i, token_len);
			if (!result[word])
				return (free_tokens(result, word), NULL);
			word++;
			i += token_len;
		}
	}
	result[word] = NULL;
	return (result);
}
