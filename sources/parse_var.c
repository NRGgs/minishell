/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 10:44:05 by nmattos           #+#    #+#             */
/*   Updated: 2024/12/20 12:55:15 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*	Check if the string is a variable.
 *
 *	str: the string to be checked.
 *
 *	Return: true / false.
 */
bool	is_variable(char *str)
{
	if (ft_strstr(str, "=\"") == NULL)
		return (false);
	return (true);
}

/*	Parse the variable from the string, and insert into linked list.
 *
 *	str: the string to be parsed.
 *
 * 	Return: SUCCESS (1) / FAIL (0).
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

/*	Replace the variable in the string.
 *
 *	str: the string to be replaced.
 *
 *	Return: the new string.
 *			NULL if failed.
 */
char	*replace_variable(char *str, t_variable *vars)
{
	t_variable	*variable;
	char		*new_str;
	char		*to_replace;
	int			i;

	to_replace = ft_strchr(str, '$');
	if (to_replace == NULL)
		return (str);
	i = 0;
	while (to_replace[i] != ' ' && to_replace[i] != '\0')
		i++;
	to_replace = ft_strndup(to_replace, i);
	if (to_replace == NULL)
		return (NULL);
	to_replace[0] = '$';
	variable = var_find(vars, to_replace + 1);
	if (variable == NULL)
	{
		free(to_replace);
		return (str);
	}
	new_str = ft_strreplace(str, to_replace, variable->value);
	free(to_replace);
	return (new_str);
}
