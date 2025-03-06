/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:21:35 by iriadyns          #+#    #+#             */
/*   Updated: 2025/03/06 10:19:47 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	free_split(char **split)
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

static int	process_echo_options(char **args, int *start_index)
{
	int	flag;
	int	i;
	int	j;

	i = 0;
	flag = 0;
	while (args[i])
	{
		if (ft_strncmp(args[i], "-n", 2) == 0)
		{
			j = 1;
			while (args[i][j] && args[i][j] == 'n')
				j++;
			if (args[i][j] == '\0')
			{
				flag = 1;
				i++;
				continue ;
			}
		}
		break ;
	}
	*start_index = i;
	return (flag);
}

int	echo(t_command *command, t_shell *shell)
{
	int		flag;
	int		start_index;
	char	**args;

	if (!command)
		return (1);
	if (!command->pattern)
		return (ft_putstr_fd("\n", STDOUT_FILENO), 0);
	args = ft_split(command->pattern, ' ');
	if (!args)
		return (1);
	flag = process_echo_options(args, &start_index);
	if (prepare_arg(command->env_list, &command->pattern, shell) == FAIL)
		return (1);
	ft_putstr_fd(command->pattern, STDOUT_FILENO);
	if (!flag)
		ft_putstr_fd("\n", STDOUT_FILENO);
	free_split(args);
	return (0);
}
