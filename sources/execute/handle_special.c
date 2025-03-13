/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_special.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:14:09 by iriadyns          #+#    #+#             */
/*   Updated: 2025/03/13 16:15:20 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_env_value(t_env *env_list, char *name)
{
	t_env	*var;

	var = find_env_var(env_list, name);
	if (var)
		return (var->value);
	return (NULL);
}

static void	handle_pwd_command(t_command *cmd, t_env *env_list, t_shell *shell)
{
	char		*temp;
	struct stat	st;

	temp = get_env_value(env_list, "PWD");
	if (temp)
	{
		if (stat(temp, &st) == 0 && S_ISDIR(st.st_mode))
		{
			ft_putstr_fd(temp, 2);
			ft_putstr_fd(": Is a directory\n", 2);
			shell->exit_status = IS_DIRECTORY;
			free(cmd->command);
			cmd->command = ft_strdup("");
			return ;
		}
		free(cmd->command);
		cmd->command = ft_strdup(temp);
	}
}

static void	handle_empty_command(t_command *cmd, t_shell *shell)
{
	shell->exit_status = 0;
	free(cmd->command);
	cmd->command = ft_strdup("");
}

void	handle_special_commands_in_structure(t_command *cmd,
		t_env *env_list, t_shell *shell)
{
	if (!cmd || !cmd->command)
		return ;
	if (ft_strcmp(cmd->command, "$PWD") == 0)
		handle_pwd_command(cmd, env_list, shell);
	else if (ft_strcmp(cmd->command, "$EMPTY") == 0)
		handle_empty_command(cmd, shell);
}
