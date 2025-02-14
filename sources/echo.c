/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:21:35 by iriadyns          #+#    #+#             */
/*   Updated: 2025/02/14 12:46:56 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*	Removes the delimiter from a string.
 *
 *	str:		The string to remove the delimiter from.
 *	delimiter:	The character to remove.
 *
 *	Return:		A new string without the delimiter.
 */
// static char	*remove_delimiter(char *str, char delimiter)
// {
// 	char	*new_str;
// 	int		i;
// 	int		j;
// 	new_str = malloc(ft_strlen(str));
// 	if (new_str == NULL)
// 	{
// 		free(str);
// 		return (NULL);
// 	}
// 	i = 0;
// 	j = 0;
// 	while (str[i] != '\0')
// 	{
// 		if (str[i] != delimiter)
// 		{
// 			new_str[j] = str[i];
// 			j++;
// 		}
// 		i++;
// 	}
// 	new_str[j] = '\0';
// 	return (new_str);
// }

// static int	print_arg_with_env(t_env *env_list, char *arg, char quote)
// {
// 	t_env	*var;
// 	char	*str;

// 	str = remove_delimiter(arg, quote);
// 	if (str == NULL)
// 		return (-1);
// 	if (str[0] == '$' && quote != '\'')
// 	{
// 		if (ft_strcmp("?", str + 1) == 0)
// 		{
// 			ft_putnbr_fd(g_exit_status, STDOUT_FILENO);
// 			return (0);
// 		}
// 		var = find_env_var(env_list, str + 1);
// 		if (var && var->value)
// 			ft_putstr_fd(var->value, STDOUT_FILENO);
// 		else
// 			ft_putstr_fd("", STDOUT_FILENO);
// 	}
// 	else
// 		ft_putstr_fd(str, STDOUT_FILENO);
// 	return (0);
// }

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
	return (str);
}

static bool	is_escaped(char *str, char *c)
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

static char	*get_nth_var(char *str, int nth_var)
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

static int	handle_variables(t_env *env_list, char **arg)
{
	char	*var_ptr;
	int		nth_var;

	var_ptr = ft_strchr(*arg, '$');
	nth_var = 0;
	while (var_ptr)
	{
		if (is_escaped(*arg, var_ptr) == false)
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

static int	print_arg(t_env *env_list, char *arg)
{
	if (handle_variables(env_list, &arg) == FAIL)
		return (FAIL);
	ft_putstr_fd(arg, STDOUT_FILENO);
	free(arg);
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


	printf("IN ECHO: command->pattern: %s\n", command->pattern);
	if (print_arg(command->env_list, command->pattern) == FAIL)
		return (1);


	// Dont touch this
	if (!flag)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}

void	ft_free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
