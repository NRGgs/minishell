/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:42:55 by nmattos-          #+#    #+#             */
/*   Updated: 2025/03/06 11:00:00 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

bool	valid_export_arg(char *arg, t_shell *shell)
{
	int		i;
	char	*equal_sign;

	i = 0;
	while (ft_isalnum(arg[i]) || arg[i] == ' ')
		i++;
	equal_sign = ft_strchr(arg, '=');
	if (!equal_sign)
		if (arg[i] == '\0' && ft_isalpha(arg[0]))
			return (true);
	if (equal_sign)
		if (arg[i] == '=' && ft_isalpha(arg[0]))
			return (true);
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	shell->exit_status = 11;
	return (false);
}
