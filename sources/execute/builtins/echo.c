/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmattos- <nmattos-@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/04 13:21:35 by iriadyns      #+#    #+#                 */
/*   Updated: 2025/03/01 17:02:08 by nmattos       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	check_echo_option(char *option);

int	echo(t_command *command, t_shell *shell)
{
	int		flag;

	if (!command)
		return (1);
	if (!command->pattern)
		return (ft_putstr_fd("\n", STDOUT_FILENO), 0);
	flag = check_echo_option(command->options);
	if (prepare_arg(command->env_list, &command->pattern, shell) == FAIL)
		return (1);
	ft_putstr_fd(command->pattern, STDOUT_FILENO);
	if (!flag)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}

static int	check_echo_option(char *option)
{
	if (!option || ft_strncmp(option, "-n", 2) != 0)
		return (0);
	return (1);
}
