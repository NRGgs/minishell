/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 17:13:07 by iriadyns          #+#    #+#             */
/*   Updated: 2025/02/17 14:57:33 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief Implements the pwd built-in command.
 * Prints the current working directory.
 *
 * @param argv The arguments passed to pwd.
 *
 * @return 0 on success, non-zero on failure.
 */
int	pwd(char **argv)
{
	char	*cwd;

	if (*(argv + 1) && check_option(*(argv + 1)) == 1)
	{
		ft_putstr_fd("pwd: invalid option -- '", STDERR_FILENO);
		ft_putstr_fd(argv[1], STDERR_FILENO);
		ft_putstr_fd("'\n", STDERR_FILENO);
		return (1);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("pwd");
		return (1);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}
