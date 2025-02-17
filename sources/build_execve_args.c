/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_execve_args.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:25:30 by iriadyns          #+#    #+#             */
/*   Updated: 2025/02/17 15:12:51 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief Counts the number of tokens in a NULL-terminated array.
 * Iterates through the array until a NULL pointer is found.
 *
 * @param arr The array of strings.
 *
 * @return The number of tokens in the array.
 */
static int	count_tokens(char **arr)
{
	int	count;

	count = 0;
	while (arr[count])
		count++;
	return (count);
}

/**
 * @brief Appends tokens from the source array into the destination array.
 * Duplicates each string from src and stores it into dst starting at index *i.
 * Updates the index *i accordingly.
 *
 * @param dst The destination array where tokens will be copied.
 *
 * @param src The source array of tokens.
 *
 * @param i Pointer to the current index in dst.
 */
static void	append_tokens(char **dst, char **src, int *i)
{
	int	j;

	j = 0;
	while (src[j])
	{
		dst[*i] = ft_strdup(src[j]);
		(*i)++;
		j++;
	}
}

/**
 * @brief Splits the options and pattern strings into tokens
 * and computes total count.
 * If options or pattern exist in the command structure, splits them by space,
 * counts the tokens, and updates the total count.
 *
 * @param cmd The command structure.
 *
 * @param opt Pointer to store the array of option tokens.
 *
 * @param pat Pointer to store the array of pattern tokens.
 *
 * @param cnt Pointer to the total count of tokens
 * (starting at 1 for the command itself).
 */
static void	get_opt_and_pat(t_command *cmd, char ***opt, char ***pat, int *cnt)
{
	*cnt = 1;
	if (cmd->options)
	{
		*opt = ft_split(cmd->options, ' ');
		*cnt += count_tokens(*opt);
	}
	else
		*opt = NULL;
	if (cmd->pattern)
	{
		*pat = ft_split(cmd->pattern, ' ');
		*cnt += count_tokens(*pat);
	}
	else
		*pat = NULL;
}

/**
 * @brief Builds the argument vector for execve from a command structure.
 * Splits the options and pattern strings into tokens,
 * allocates an array of strings,
 * and concatenates them with the command name as the first argument.
 * The resulting array is NULL-terminated.
 *
 * @param cmd The command structure.
 *
 * @return A dynamically allocated NULL-terminated array
 * of strings (argv) or NULL on failure.
 */
char	**build_execve_args(t_command *cmd)
{
	char	**opt;
	char	**pat;
	char	**args;
	int		cnt;
	int		i;

	get_opt_and_pat(cmd, &opt, &pat, &cnt);
	args = malloc(sizeof(char *) * (cnt + 1));
	if (!args)
	{
		free_2d_array(opt);
		free_2d_array(pat);
		return (NULL);
	}
	i = 0;
	args[i++] = ft_strdup(cmd->command);
	if (opt)
		append_tokens(args, opt, &i);
	if (pat)
		append_tokens(args, pat, &i);
	args[i] = NULL;
	free_2d_array(opt);
	free_2d_array(pat);
	return (args);
}
