/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:46:46 by nmattos-          #+#    #+#             */
/*   Updated: 2025/02/14 13:32:43 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// static int	special_parse_pattern(char **input, int *i, char **pattern);
static int	parse_options(char **input, int *i, char **options);
static char	*get_pattern(char **input, int *i, char *pattern);

/*	Parse the command and its options.
 *
 *	input:	the user input.
 *	cmds:	the linked list of commands.
 *	i:		the index of the current token.
 *
 *	Return: SUCCESS (1) / FAIL (0).
 */
int	parse_command(char **input, t_command **cmds, int *i)
{
	t_command	*new_cmd;
	char		*options;
	char		*command;
	char		*pattern;

	command = input[*i];
	options = NULL;
	pattern = NULL;
	if (options_possible(command))
		if (parse_options(input, i, &options) == FAIL)
			return (FAIL);
	// if (!is_special(command))
	// 	if (special_parse_pattern(input, i, &pattern) == FAIL)
	// 		return (FAIL);
	new_cmd = cmd_new(command, options);
	if (options != NULL)
		free(options);
	if (new_cmd == NULL)
		return (FAIL);
	if (input[*i + 1] != NULL && !is_command(input[*i + 1])
		&& !is_redirect(input[*i + 1]))
		pattern = get_pattern(input, i, pattern);
	new_cmd->pattern = pattern;
	cmd_add_back(cmds, new_cmd);
	return (SUCCESS);
}

/*	Parse the pattern of the special commands.
 *
 *	input:		the user input.
 *	i:			the index of the current token.
 *	pattern:	the pattern of the command.
 *
 *	Return: SUCCESS (1) / FAIL (0).
 */
// static int	special_parse_pattern(char **input, int *i, char **pattern)
// {
// 	size_t		size;
// 	int			j;
// 	char		quote;

// 	size = 0;
// 	j = *i;
// 	if (input[j + 1] == NULL || is_redirect(input[j + 1]))
// 		return (SUCCESS);
// 	quote = contains_quote(input[j + 1]);
// 	if (quote != '0')
// 	{
// 		(*i)++;
// 		if (parse_string(input, i, pattern, quote) == FAIL)
// 			return (FAIL);
// 		printf("WE DID IT pattern: %s\n", *pattern);
// 		return (SUCCESS);
// 	}
// 	size = ft_strlen(input[j + 1]);
// 	*pattern = ft_calloc((size + 1), sizeof(char));
// 	if (*pattern == NULL)
// 		return (FAIL);
// 	ft_strlcpy(*pattern, input[j + 1], size + 1);
// 	(*i)++;
// 	return (SUCCESS);
// }

/*	Parse the options of the command.
 *
 *	input:		the user input.
 *	i:			the index of the current token.
 *	options:	the options of the command.
 *
 *	Return: SUCCESS (1) / FAIL (0).
 */
static int	parse_options(char **input, int *i, char **options)
{
	size_t		size;
	int			j;

	size = 0;
	j = *i;
	while (input[j + 1] != NULL && input[j + 1][0] == '-')
	{
		j++;
		size += ft_strlen(input[j]);
	}
	if (size <= 0)
		return (SUCCESS);
	size += j - (*i)++;
	*options = ft_calloc((size + 1), sizeof(char));
	if (*options == NULL)
		return (FAIL);
	while (input[*i] != NULL && input[*i][0] == '-')
	{
		ft_strlcat(*options, input[*i], size + 1);
		if (input[*i + 1] != NULL && input[*i + 1][0] == '-')
			ft_strlcat(*options, " ", size);
		(*i)++;
	}
	(*i)--;
	return (SUCCESS);
}

/*	Get the pattern of the command.
 *
 *	input:		the user input.
 *	i:			the index of the current token.
 *	pattern:	the pattern of the command.
 *
 *	Return: the new pattern.
 */
static char	*get_pattern(char **input, int *i, char *pattern)
{
	char	*new_pattern;
	size_t	len_pattern;
	size_t	len_string;

	new_pattern = NULL;
	len_pattern = 0;
	len_string = 0;
	while (input[*i + 1] != NULL && !is_command(input[*i + 1])
		&& !is_redirect(input[*i + 1]))
	{
		len_string = ft_strlen(input[*i + 1]);
		if (pattern == NULL)
			new_pattern = ft_strdup(input[*i + 1]);
		else
		{
			len_pattern = ft_strlen(pattern) + 1;
			new_pattern = ft_strndup(pattern, len_pattern + len_string);
			space_strlcat(new_pattern, input[*i + 1], \
				len_pattern + len_string + 1);
		}
		free(pattern);
		pattern = new_pattern;
		(*i)++;
	}
	return (new_pattern);
}
