/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_string_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:03:25 by nmattos-          #+#    #+#             */
/*   Updated: 2025/02/05 12:33:51 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	contains_quote(char *str)
{
	if (ft_strchr(str, '\"') != NULL)
		return ('\"');
	if (ft_strchr(str, '\'') != NULL)
		return ('\'');
	return ('0');
}

int	n_chars_till_quote(char **input, int j)
{
	int		start;
	int		k;
	size_t	size;

	size = 0;
	start = j - 1;
	while (input[j] != NULL)
	{
		if (ft_strchr(input[j], '\"') != NULL)
		{
			k = 0;
			while (input[j][k] != '\"')
			{
				size++;
				k++;
			}
			return (size + (j - start));
		}
		size += ft_strlen(input[j]) + 1;
		j++;
	}
	return (size);
}

static char	*remove_delimiter(char *str, char delimiter)
{
	char	*new_str;
	int		i;
	int		j;

	new_str = malloc(ft_strlen(str));
	if (new_str == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] != delimiter)
		{
			new_str[j] = str[i];
			j++;
		}
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

static char	*attach_buffer(char *pattern, char *buffer)
{
	char	*temp;

	pattern = add_newline(pattern);
	if (pattern == NULL)
		return (free(buffer), NULL);
	temp = ft_strjoin(pattern, buffer);
	free(buffer);
	if (temp == NULL)
		return (free(pattern), NULL);
	free(pattern);
	pattern = ft_strdup(temp);
	if (pattern == NULL)
		return (free(temp), NULL);
	free(temp);
	return (pattern);
}

char	*read_till_quotes(char delimiter, char **pattern)
{
	char	*buffer;
	bool	reading;

	reading = true;
	while (reading)
	{
		buffer = readline("\\ ");
		if (buffer != NULL && ft_strchr(buffer, delimiter) != NULL)
		{
			buffer = remove_delimiter(buffer, delimiter);
			if (buffer == NULL)
				return (NULL);
			reading = false;
		}
		*pattern = attach_buffer(*pattern, buffer);
		if (*pattern == NULL)
			return (NULL);
	}
	return (*pattern);
}
