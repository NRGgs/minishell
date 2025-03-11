/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:49:08 by iriadyns          #+#    #+#             */
/*   Updated: 2025/03/11 14:58:55 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_all_delim(const char *s, char c)
{
	int	i;
	int	all;

	i = 0;
	all = 1;
	while (s[i])
	{
		if (s[i] != c && s[i] != '\001')
		{
			all = 0;
			break ;
		}
		i++;
	}
	return (all);
}

static int	count_tokens_split(const char *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && (s[i] == c || s[i] == '\001'))
			i++;
		if (s[i])
		{
			count++;
			while (s[i] && s[i] != c && s[i] != '\001')
				i++;
		}
	}
	return (count);
}

char	**special_split(char const *s, char c)
{
	char	**result;
	int		token_count;

	if (s == NULL)
		return (NULL);
	if (*s == '\0')
	{
		result = malloc(2 * sizeof(char *));
		if (!result)
			return (NULL);
		result[0] = ft_strdup("");
		result[1] = NULL;
		return (result);
	}
	if (is_all_delim(s, c))
	{
		result = malloc(2 * sizeof(char *));
		result[0] = ft_strdup(s);
		result[1] = NULL;
		return (result);
	}
	token_count = count_tokens_split(s, c);
	result = fill_tokens(s, c, token_count);
	return (result);
}
