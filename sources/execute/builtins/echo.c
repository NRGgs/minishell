/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:21:35 by iriadyns          #+#    #+#             */
/*   Updated: 2025/03/13 11:11:48 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	check_for_echo_option(t_command *command, bool *flag);

int	echo(t_command *command, t_shell *shell)
{
	bool	flag;

	if (!command)
		return (1);
	// if (command->options && command->options[0] != '\0')
	// 	flag = 1;
	// else
	// 	flag = 0;
	flag = false;
	if (check_for_echo_option(command, &flag) == FAIL)
		return (1);
	if (!command->pattern)
		return (ft_putstr_fd("\n", STDOUT_FILENO), 0);
	if (prepare_arg(command->env_list, &command->pattern, shell) == FAIL)
		return (1);
	ft_putstr_fd(command->pattern, STDOUT_FILENO);
	if (!flag)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}

static int	check_for_echo_option(t_command *command, bool *flag)
{
	char	*option;
	char	*temp;
	int		i;

	option = command->options;
	if (!option)
		return (SUCCESS);
	if (option[1] == 'n')
	{
		i = 1;
		while (option[i] == 'n')
			i++;
		if (option[i] == ' ' || option[i] == '\0')
		{
			while (option[i] == ' ')
				i++;
			temp = malloc(ft_strlen(option + i) + ft_strlen(command->pattern) + 2);
			if (!temp)
				return (FAIL);
			temp[0] = '\0';
			ft_strlcat(temp, (option + i), ft_strlen(option + i) + ft_strlen(command->pattern) + 2);
			ft_strlcat(temp, " ", ft_strlen(option + i) + ft_strlen(command->pattern) + 2);
			ft_strlcat(temp, command->pattern, ft_strlen(option + i) + ft_strlen(command->pattern) + 2);
			if (!temp)
				return (FAIL);
			free(command->pattern);
			command->pattern = temp;
			*flag = true;
			return (SUCCESS);
		}
	}
	if (!command->pattern)
		temp = ft_strndup(option, sizeof(option));
	else
	{
		temp = malloc(ft_strlen(option) + ft_strlen(command->pattern) + 2);
		if (!temp)
			return (FAIL);
		temp[0] = '\0';
		ft_strlcat(temp, option, ft_strlen(option) + ft_strlen(command->pattern) + 2);
		ft_strlcat(temp, " ", ft_strlen(option) + ft_strlen(command->pattern) + 2);
		ft_strlcat(temp, command->pattern, ft_strlen(option) + ft_strlen(command->pattern) + 2);
	}
	if (!temp)
		return (FAIL);
	free(command->pattern);
	command->pattern = temp;
	return (SUCCESS);
}
