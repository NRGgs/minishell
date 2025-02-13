/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmattos- <nmattos-@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/04 13:21:35 by iriadyns      #+#    #+#                 */
/*   Updated: 2025/02/13 16:43:27 by nmattos       ########   odam.nl         */
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

	i = 0;
	to_replace = var_ptr;
	i = 1;
	while (valid_char(to_replace[i]))
		i++;
	to_replace = ft_strndup(to_replace, i);
	if (to_replace == NULL)
		return (NULL);
	to_replace[0] = '$';
	var = find_env_var(env_list, to_replace + 1);
	if (var && var->value)
		str = ft_strreplace(str, to_replace, var->value);
	else
		str = ft_strreplace(str, to_replace, "");
	return (str);
}

static int	print_arg_with_env_2(t_env *env_list, char *arg)
{
	// t_env	*var;
	char	*var_ptr;

	var_ptr = ft_strchr(arg, '$');
	// if (var_ptr && is_escaped(&var_ptr) == false)
	while (var_ptr)
	{
		arg = replace_var(arg, var_ptr, env_list);
		var_ptr = ft_strchr(var_ptr + 1, '$');
	}
	ft_putstr_fd(arg, STDOUT_FILENO);
	return (0);
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
	// char	**args;
	// int		i;

	if (!command)
		return (1);
	if (!command->pattern)
		return (ft_putstr_fd("\n", STDOUT_FILENO), 0);
	flag = check_echo_option(command->options);
	// args = ft_split(command->pattern, ' ');
	// if (!args)
		// return (1);
	// i = 0;
	// while (args[i])
	// {
	// 	if (print_arg_with_env(command->env_list, args[i], command->pattern[0]) == -1)
	// 		return (ft_free_split(args), 1);
	// 	if (args[i + 1])
	// 		ft_putstr_fd(" ", STDOUT_FILENO);
	// 	i++;
	// }
	printf("IN ECHO: command->pattern: %s\n", command->pattern);

	print_arg_with_env_2(command->env_list, command->pattern);

	// Dont touch this
	if (!flag)
		ft_putstr_fd("\n", STDOUT_FILENO);
	// ft_free_split(args);
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
