/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:21:35 by iriadyns          #+#    #+#             */
/*   Updated: 2025/03/13 12:39:23 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	copy_tokens(char **tokens, int start_index, char *result)
{
	int	i;
	int	j;
	int	pos;

	pos = 0;
	i = start_index;
	while (tokens[i])
	{
		j = 0;
		while (tokens[i][j])
		{
			result[pos] = tokens[i][j];
			pos++;
			j++;
		}
		i++;
		if (tokens[i])
		{
			result[pos] = ' ';
			pos++;
		}
	}
	result[pos] = '\0';
}

char	*join_tokens(char **tokens, int start_index)
{
	int		total_len;
	char	*result;

	total_len = compute_total_length(tokens, start_index);
	result = malloc(total_len + 1);
	if (!result)
		return (NULL);
	copy_tokens(tokens, start_index, result);
	return (result);
}

static int	join_space_length(char *s1, char *s2)
{
	int	len1;
	int	len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	return (len1 + len2 + 2);
}

static void	copy_join_with_space(char *s1, char *s2, char *result)
{
	int	pos;
	int	i;
	int	j;

	pos = 0;
	i = 0;
	while (s1[i])
	{
		result[pos] = s1[i];
		pos++;
		i++;
	}
	result[pos] = ' ';
	pos++;
	j = 0;
	while (s2[j])
	{
		result[pos] = s2[j];
		pos++;
		j++;
	}
	result[pos] = '\0';
}

char	*join_with_space(char *s1, char *s2)
{
	int		total_len;
	char	*result;

	total_len = join_space_length(s1, s2);
	result = malloc(total_len);
	if (!result)
		return (NULL);
	copy_join_with_space(s1, s2, result);
	return (result);
}
