/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:56:52 by iriadyns          #+#    #+#             */
/*   Updated: 2025/01/28 12:55:56 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exit_shell(char *input)
{
	int	exit_code;

	if (!input)
		exit_code = g_exit_status;
	else
	{
		exit_code = ft_atoi(input, &exit_code);
	}
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	exit(exit_code);
}
