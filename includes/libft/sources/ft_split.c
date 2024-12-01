/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos <nmattos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 10:13:52 by nmattos-          #+#    #+#             */
/*   Updated: 2024/12/01 10:27:42 by nmattos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	get_word_count(char *s, char c)
{
	int	word_count;

	word_count = 0;
	if (*s == '\0')
		return (0);
	if (c == 0)
		return (1);
	while (*s == c)
		s++;
	while (*s != '\0')
	{
		if (*s == c)
		{
			word_count++;
			while (*s == c)
				s++;
		}
		else
			s++;
	}
	if (*(s - 1) != c)
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

static char	**allocate_words(char *s, char c, char **result)
{
	int	length;
	int	nth_word;

	nth_word = 0;
	length = 1;
	while (*s == c)
		s++;
	while (*s != '\0')
	{
		while (*s != '\0' && *(s++) != c)
			length++;
		if (length > 0)
		{
			result[nth_word] = malloc((length) * sizeof(char));
			if (result[nth_word] == NULL)
				return (free_result(result, nth_word - 1), NULL);
			length = 1;
			nth_word++;
		}
		while (*s == c && *s != '\0')
			s++;
	}
	return (result);
}

static char	**split_words(char *s, char c, char **result)
{
	int	i;
	int	nth_word;

	nth_word = 0;
	i = 0;
	while (*s == c)
		s++;
	while (*s != '\0')
	{
		while (*s != '\0' && *s != c)
			result[nth_word][i++] = *(s++);
		result[nth_word++][i] = '\0';
		i = 0;
		while (*s == c && *s != '\0')
			s++;
	}
	result[nth_word] = NULL;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;

	if (s == NULL)
		return (NULL);
	result = malloc((get_word_count((char *)s, c) + 1) * sizeof(char *));
	if (result == NULL)
		return (NULL);
	if (get_word_count((char *)s, c) == 0)
	{
		result[0] = NULL;
		return (result);
	}
	result = allocate_words((char *)s, c, result);
	if (result == NULL)
		return (NULL);
	result = split_words((char *)s, c, result);
	return (result);
}
