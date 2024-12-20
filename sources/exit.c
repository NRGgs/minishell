/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:56:52 by iriadyns          #+#    #+#             */
/*   Updated: 2024/12/20 12:56:04 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int exit_shell(char *input)
{
	int exit_code;

	if (!input)
		exit_code = 0;
	else
	{
		exit_code = ft_atoi(input, &exit_code);
	}
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	exit(exit_code);
}
