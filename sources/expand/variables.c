/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:48:49 by nmattos-          #+#    #+#             */
/*   Updated: 2025/02/18 10:57:01 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*var_exit_status(char *str, char *var_ptr);

/**
 * @brief Replaces the variable in the argument with its value.
 *
 * @param str		The argument to prepare.
 * @param var_ptr	The pointer to the variable.
 * @param env_list	The environment variables list.
 * @return 			The new argument.
 */
char	*replace_var(char *str, char *var_ptr, t_env *env_list)
{
	t_env	*var;
	char	*to_replace;
	int		i;

	to_replace = var_ptr;
	if (ft_strncmp(to_replace, "$?", 2) == 0)
		return (var_exit_status(str, var_ptr));
	i = 1;
	while (valid_char(to_replace[i]))
		i++;
	to_replace = ft_strndup(to_replace, i);
	if (to_replace == NULL)
		return (free(str), NULL);
	to_replace[0] = '$';
	var = find_env_var(env_list, to_replace + 1);
	if (var && var->value)
		str = ft_strreplace(str, to_replace, var->value, var_ptr);
	else
		str = ft_strreplace(str, to_replace, "", var_ptr);
	free(to_replace);
	return (str);
}

/**
 * @brief Replaces the exit status variable in the argument with its value.
 *
 * @param str		The argument to prepare.
 * @param var_ptr	The pointer to the variable.
 * @return 			The new argument.
 */
static char	*var_exit_status(char *str, char *var_ptr)
{
	char	*exit_status;
	char	*new_str;

	exit_status = ft_itoa(g_exit_status);
	if (exit_status == NULL)
		return (free(str), NULL);
	new_str = ft_strreplace(str, "$?", exit_status, var_ptr);
	free(exit_status);
	return (new_str);
}

/**
 * @brief Checks if the character is escaped.
 *
 * @param str	The string to check.
 * @param c		The character to check.
 * @return 		True if the character is escaped, false otherwise.
 */
bool	char_is_escaped(char *str, char *c)
{
	bool	escaped;

	escaped = false;
	while (str < c)
	{
		if (*str == '\\')
			escaped = !escaped;
		else if (*str != '\\')
			escaped = false;
		str++;
	}
	return (escaped);
}

/**
 * @brief Checks if the character is in single quotes.
 *
 * @param str	The string to check.
 * @param c		The character to check.
 * @return 		True if the character is in single quotes, false otherwise.
 */
bool	in_single_quotes(char *str, char *c)
{
	bool	in_single;
	bool	in_double;
	int		i;

	in_single = false;
	in_double = false;
	i = 0;
	while (str + i < c)
	{
		if (str[i] == '\'' && !in_double
			&& char_is_escaped(str, str + i) == false)
			in_single = !in_single;
		else if (str[i] == '\"' && !in_single
			&& char_is_escaped(str, str + i) == false)
			in_double = !in_double;
		i++;
	}
	if (in_single)
		return (true);
	return (false);
}

/**
 * @brief Gets the nth variable in the string.
 *
 * @param str		The string to check.
 * @param nth_var	The number of the variable to get.
 * @return 			The pointer to the variable.
 */
char	*get_nth_var(char *str, int nth_var)
{
	char	*var_ptr;

	var_ptr = ft_strchr(str, '$');
	while (var_ptr && nth_var > 0)
	{
		var_ptr = ft_strchr(var_ptr + 1, '$');
		nth_var--;
	}
	return (var_ptr);
}
