/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 16:57:52 by iriadyns          #+#    #+#             */
/*   Updated: 2024/12/01 16:58:17 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

int	exec_builtin(char **argv)
{
	if (!ft_strncmp(*argv, "cd", 3))
		return (cd(argv));
	if (!ft_strncmp(*argv, "echo", 5))
		return (echo(argv));
	if (!ft_strncmp(*argv, "pwd", 4))
		return (pwd(argv));
	if (!ft_strncmp(*argv, "env", 4))
		return (env(argv));
	if (!ft_strncmp(*argv, "export", 7))
		return (export(argv));
	if (!ft_strncmp(*argv, "unset", 6))
		return (unset(argv));
	if (!ft_strncmp(*argv, "exit", 5))
		exit(argv);
	return (1);
}
