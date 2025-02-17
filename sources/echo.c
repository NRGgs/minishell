/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:21:35 by iriadyns          #+#    #+#             */
/*   Updated: 2025/02/17 11:08:47 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	quote_backslash_handler(char **str, char **new_str, int *i, int *j)
{
	size_t	consecutive_backslashes;
	bool	escaped;

	escaped = false;
	consecutive_backslashes = 0;
	while ((*str)[*i] == '\\')
	{
		consecutive_backslashes++;
		(*i)++;
	}
	if (consecutive_backslashes % 2 == 1)
		escaped = true;
	if ((*str)[*i] == '\'' || (*str)[*i] == '\"')
		consecutive_backslashes /= 2;
	while (consecutive_backslashes-- > 0)
		(*new_str)[(*j)++] = '\\';
	consecutive_backslashes = 0;
	return (escaped);
}

/*	Removes the quotes from a string.
 *
 *	str:		The string to remove the quotes from.
 *
 *	Return:		A new string without quotes.
 */
static int	handle_quotes(char **str)
{
	char	*new_str;
	int		i;
	int		j;
	bool	in_single;
	bool	in_double;

	new_str = malloc((ft_strlen(*str) + 1) * sizeof(char));
	if (new_str == NULL)
		return (free(str), FAIL);
	i = 0;
	j = 0;
	in_single = false;
	in_double = false;
	while (*(*str + i) != '\0')
	{
		if (*(*str + i) == '\'')
		{
			if (!in_double)
				in_single = !in_single;
			if (in_double)
				new_str[j++] = *(*str + i);
			i++;
		}
		else if (*(*str + i) == '\"')
		{
			if (!in_single)
				in_double = !in_double;
			if (in_single)
				new_str[j++] = *(*str + i);
			i++;
		}
		if (*(*str + i) == '\\')
			quote_backslash_handler(str, &new_str, &i, &j);
		new_str[j++] = *(*str + i++);
	}
	new_str[j] = '\0';
	free(*str);
	*str = new_str;
	return (SUCCESS);
}

static char	*replace_var(char *str, char *var_ptr, t_env *env_list)
{
	t_env	*var;
	char	*to_replace;
	int		i;

	to_replace = var_ptr;
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

static int	handle_variables(t_env *env_list, char **arg)
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
			*arg = replace_var(*arg, var_ptr, env_list);
			if (*arg == NULL)
				return (FAIL);
		}
		else
			nth_var++;
		var_ptr = get_nth_var(*arg, nth_var);
	}
	return (SUCCESS);
}

static bool	back_backslash_handler(char **str, char **new_str, int *i, int *j)
{
	size_t	consecutive_backslashes;
	bool	escaped;

	escaped = false;
	consecutive_backslashes = 0;
	while ((*str)[*i] == '\\')
	{
		consecutive_backslashes++;
		(*i)++;
	}
	if (consecutive_backslashes % 2 == 1)
		escaped = true;
	if ((*str)[*i] != '\'' && (*str)[*i] != '\"')
		consecutive_backslashes /= 2;
	while (consecutive_backslashes-- > 0)
		(*new_str)[(*j)++] = '\\';
	consecutive_backslashes = 0;
	return (escaped);
}

static int	handle_backslashes(char **arg)
{
	char	*new_str;
	int		i;
	int		j;
	bool	in_single;
	bool	in_double;
	bool	escaped;

	new_str = malloc((ft_strlen(*arg) + 1) * sizeof(char));
	if (new_str == NULL)
		return (free(arg), FAIL);
	i = 0;
	j = 0;
	in_single = false;
	in_double = false;
	escaped = false;
	while ((*arg)[i] != '\0')
	{
		if ((*arg)[i] == '\'' && !in_double)
		{
			if (escaped == false)
				in_single = !in_single;
			else if (escaped == true && in_single == true)
				in_single = !in_single;
			escaped = false;
		}
		else if ((*arg)[i] == '\"' && !in_single && escaped == false)
			in_double = !in_double;
		else if ((*arg)[i] == '\\' && !in_single)
			escaped = back_backslash_handler(arg, &new_str, &i, &j);
		else
			escaped = false;
		new_str[j++] = (*arg)[i++];
	}
	new_str[j] = '\0';
	free(*arg);
	*arg = new_str;
	return (SUCCESS);
}

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

static int	print_arg(t_env *env_list, char **arg)
{
	if (handle_variables(env_list, arg) == FAIL)
		return (FAIL);
	if (handle_backslashes(arg) == FAIL)
		return (FAIL);
	if (handle_quotes(arg) == FAIL)
		return (FAIL);
	trim_memory(arg);
	ft_putstr_fd(*arg, STDOUT_FILENO);
	return (SUCCESS);
}

int	check_echo_option(char *option)
{
	if (!option || ft_strncmp(option, "-n", 2) != 0)
		return (0);
	return (1);
}

int	echo(t_command *command)
{
	int		flag;

	if (!command)
		return (1);
	if (!command->pattern)
		return (ft_putstr_fd("\n", STDOUT_FILENO), 0);
	flag = check_echo_option(command->options);
	if (print_arg(command->env_list, &command->pattern) == FAIL)
		return (1);
	if (!flag)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
