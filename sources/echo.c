/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:21:35 by iriadyns          #+#    #+#             */
/*   Updated: 2025/01/21 15:01:14 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

	if (!command || !command->pattern)
		return (1);

	flag = check_echo_option(command->options);
	args = ft_split(command->pattern, ' ');
	if (!args)
		return (1);
	i = 0;
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
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
		return;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
