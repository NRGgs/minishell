/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:40:33 by nmattos           #+#    #+#             */
/*   Updated: 2025/02/26 10:57:07 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	skip_spaces(char **s)
{
	while (**s == ' '
		|| **s == '\f'
		|| **s == '\r'
		|| **s == '\n'
		|| **s == '\t'
		|| **s == '\v')
		(*s)++;
}

bool	skip_escapes(char *s, size_t *len, bool escaped)
{
	if (s[*len] != '\\')
		return (false);
	while (s[*len] == '\\')
	{
		escaped = !escaped;
		(*len)++;
	}
	return (escaped);
}

bool	is_delimiter(char *s, bool escaped)
{
	if (*s == ' '
		|| *s == '\0'
		|| *s == '\f'
		|| *s == '\r'
		|| *s == '\n'
		|| *s == '\t'
		|| *s == '\v')
		return (true);
	if (!escaped
		&& (ft_strncmp(s, "<<", 2) == 0
			|| ft_strncmp(s, ">>", 2) == 0
			|| *s == '|'
			|| *s == '<'
			|| *s == '>'))
		return (true);
	return (false);
}

bool	is_redirect(char *s)
{
	if (ft_strncmp(s, "<<", 2) == 0
		|| ft_strncmp(s, ">>", 2) == 0
		|| *s == '<'
		|| *s == '>')
		return (true);
	return (false);
}

bool	is_option(char *s)
{
	if (*s == '-')
		return (true);
	return (false);
}
