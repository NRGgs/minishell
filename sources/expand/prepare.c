/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:47:31 by nmattos-          #+#    #+#             */
/*   Updated: 2025/03/05 12:30:49 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	handle_backslashes(char **arg);
static int	handle_quotes(char **str);
static int	trim_memory(char **str);

/**
 * @brief Prepares the argument for execution by handling its
 * variables, backslashes, and quotes.
 *
 * @param env_list	The environment variables list.
 * @param arg		The argument to prepare.
 * @return int		SUCCESS or FAIL.
 */
int	prepare_arg(t_env *env_list, char **arg, t_shell *shell)
{
	if (handle_variables(env_list, arg, shell) == FAIL)
		return (FAIL);
	if (handle_backslashes(arg) == FAIL)
		return (FAIL);
	if (handle_quotes(arg) == FAIL)
		return (FAIL);
	trim_memory(arg);
	return (SUCCESS);
}

/**
 * @brief Replaces the variables in the argument with their values.
 *
 * @param env_list	The environment variables list.
 * @param arg		The argument to prepare.
 * @return int		SUCCESS or FAIL.
 */
int	handle_variables(t_env *env_list, char **arg, t_shell *shell)
{
	char	*var_ptr;
	int		nth_var;

	var_ptr = ft_strchr(*arg, '$');
	nth_var = 0;
	while (var_ptr)
	{
		if (char_is_escaped(*arg, var_ptr) == false
			&& in_single_quotes(*arg, var_ptr) == false)
		{
			*arg = replace_var(*arg, var_ptr, env_list, shell);
			if (*arg == NULL)
				return (FAIL);
		}
		else
			nth_var++;
		var_ptr = get_nth_var(*arg, nth_var);
	}
	return (SUCCESS);
}

/**
 * @brief Handles backslashes in the argument.
 *
 * @param arg	The argument to prepare.
 * @return int	SUCCESS or FAIL.
 * @note		Backslashes are used to escape characters in the argument.
 */
static int	handle_backslashes(char **arg)
{
	char	*new_str;
	int		i;
	int		j;
	int		in_quotes;
	bool	escaped;

	new_str = malloc((ft_strlen(*arg) + 1) * sizeof(char));
	if (new_str == NULL)
		return (free(arg), FAIL);
	i = 0;
	j = 0;
	in_quotes = FALSE;
	escaped = false;
	while ((*arg)[i] != '\0')
	{
		if (check_quotes((*arg)[i], &in_quotes, &escaped))
			escaped = false;
		else if ((*arg)[i] == '\\' && in_quotes != SINGLE)
			escaped = back_backslash_handler(arg, &new_str, &i, &j);
		new_str[j++] = (*arg)[i++];
	}
	new_str[j] = '\0';
	free(*arg);
	*arg = new_str;
	return (SUCCESS);
}

/**
 * @brief Handles quotes in the argument.
 *
 * @param str	The argument to prepare.
 * @return int	SUCCESS or FAIL.
 */
static int	handle_quotes(char **str)
{
	char	*new_str;
	int		i;
	int		j;
	int		in_quotes;

	new_str = malloc((ft_strlen(*str) + 1) * sizeof(char));
	if (new_str == NULL)
		return (free(str), FAIL);
	i = 0;
	j = 0;
	in_quotes = FALSE;
	while ((*str)[i] != '\0')
	{
		while (update_quotes(*(*str + i), &new_str, &j, &in_quotes))
			i++;
		if ((*str)[i] == '\\' && in_quotes != SINGLE)
			quote_backslash_handler(str, &new_str, &i, &j);
		if ((*str)[i] == '\0')
			break ;
		new_str[j++] = (*str)[i++];
	}
	new_str[j] = '\0';
	free(*str);
	*str = new_str;
	return (SUCCESS);
}

/**
 * @brief Trims the memory of the argument.
 *
 * @param str	The argument to trim.
 * @return int	SUCCESS or FAIL.
 */
static int	trim_memory(char **str)
{
	char	*new_str;
	size_t	size;

	size = 0;
	while ((*str)[size] != '\0')
		size++;
	new_str = ft_realloc(*str, size + 1);
	if (new_str == NULL)
		return (FAIL);
	*str = new_str;
	return (SUCCESS);
}
