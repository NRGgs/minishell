/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 10:44:05 by nmattos           #+#    #+#             */
/*   Updated: 2025/02/21 16:45:36 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Check if the string is a variable.
 *
 * @param str The string to be checked.
 * @return true if the string is a variable, false otherwise.
 */
bool	is_variable(char *str)
{
	if (ft_strstr(str, "=") == NULL)
		return (false);
	return (true);
}

/**
 * @brief Parse the variable from the string, and insert into linked list.
 *
 * @param str The string to be parsed.
 * @param vars The linked list to insert the parsed variable into.
 * @return int SUCCESS (1) / FAIL (0).
 */
int	parse_variable(char *str, t_variable **vars)
{
	t_variable	*new_var;
	size_t		len;
	char		*name;
	char		*value;

	len = ft_strchr(str, '=') - str;
	name = ft_strndup(str, len);
	if (name == NULL)
		return (FAIL);
	len = (ft_strrchr(str, '"')) - (ft_strchr(str, '"') + 1);
	value = ft_strndup(ft_strchr(str, '"') + 1, len);
	if (value == NULL)
	{
		free(name);
		return (FAIL);
	}
	new_var = var_new(name, value);
	free(name);
	free(value);
	if (new_var == NULL)
		return (FAIL);
	var_add_back(vars, new_var);
	return (SUCCESS);
}

/**
 * @brief Check if the character is valid.
 *
 * @param c The character to be checked.
 * @return true if the character is valid, false otherwise.
 */
bool	valid_char(char c)
{
	if ((c >= 65 && c <= 90)
		|| (c >= 97 && c <= 122)
		|| (c >= 48 && c <= 57))
		return (true);
	return (false);
}
