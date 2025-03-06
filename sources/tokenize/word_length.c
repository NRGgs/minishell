/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_length.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:38:15 by nmattos           #+#    #+#             */
/*   Updated: 2025/03/06 10:13:16 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t	length_redirect(char *str);
static size_t	quote_length(char *str, size_t len);

size_t	next_word_length(char *str)
{
	size_t	len;
	bool	escaped;

	len = 0;
	escaped = false;
	while (str[len] != '\0')
	{
		escaped = skip_escapes(str, &len, escaped);
		if (is_delimiter(str + len, escaped))
		{
			if (len == 0)
				return (length_redirect(str));
			return (len);
		}
		if ((str[len] == '\'' || str[len] == '\"') && !escaped)
			len = quote_length(str, len);
		len++;
	}
	return (len);
}

static size_t	quote_length(char *str, size_t len)
{
	char	quote;

	quote = str[len++];
	while (str[len] != '\0' && str[len] != quote)
		len++;
	return (len);
}

static size_t	length_redirect(char *str)
{
	if (ft_strncmp(str, "<<", 2) == 0
		|| ft_strncmp(str, ">>", 2) == 0)
		return (2);
	return (1);
}
