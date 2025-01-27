/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:21:35 by iriadyns          #+#    #+#             */
/*   Updated: 2025/01/27 14:38:03 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	print_arg_with_env(char *arg)
{
	char	*env_value;

	if (arg && arg[0] == '$')
	{
		env_value = getenv(arg + 1);
		if (env_value)
			ft_putstr_fd(env_value, STDOUT_FILENO);
		else
			ft_putstr_fd("", STDOUT_FILENO);
	}
	else
		ft_putstr_fd(arg, STDOUT_FILENO);
}

int	check_echo_option(char *option)
{
	int	i;

	if (!option || ft_strncmp(option, "-n", 2) != 0)
		return (0);
	i = 2;
	while (option[i] == 'n')
		i++;
	return (option[i] == '\0');
}

int	echo(t_command *command)
{
	int		flag;
	char	**args;
	int		i;

	if (!command)
		return (1);
	if (!command->pattern)
		return (printf("\n"), 0);
	flag = check_echo_option(command->options);
	args = ft_split(command->pattern, ' ');
	if (!args)
		return (1);
	i = 0;
	while (args[i])
	{
		print_arg_with_env(args[i]);
		if (args[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (!flag)
		ft_putstr_fd("\n", STDOUT_FILENO);
	ft_free_split(args);
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
