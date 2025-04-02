/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:56:52 by iriadyns          #+#    #+#             */
/*   Updated: 2025/03/24 16:09:14 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	exit_numeric_error(char **tokens, int *exit_code)
{
	ft_putstr_fd("exit: ", STDERR_FILENO);
	ft_putstr_fd(tokens[0], STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	free_2d_array(tokens);
	*exit_code = MAJOR;
	return (SHELL_EXIT);
}

static int	exit_too_many_args(char **tokens, int *exit_code)
{
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
	free_2d_array(tokens);
	*exit_code = MINOR;
	return (SHELL_CONTINUE);
}

static int	check_exit_tokens(char **tokens, int *exit_code)
{
	int	error;

	if (!tokens || !tokens[0] || tokens[0][0] == '\0')
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		ft_putstr_fd("exit: : numeric argument required\n", STDERR_FILENO);
		if (tokens)
			free_2d_array(tokens);
		*exit_code = MAJOR;
		return (SHELL_EXIT);
	}
	*exit_code = ft_atoi(tokens[0], &error);
	if (error)
		return (exit_numeric_error(tokens, exit_code));
	if (count_tokens(tokens) > 1)
		return (exit_too_many_args(tokens, exit_code));
	free_2d_array(tokens);
	return (-1);
}

static int	handle_exit_arg(char *pattern, t_env *env, \
			int *exit_code, t_shell *shell)
{
	char	*proc;
	char	**tokens;

	proc = ft_strdup(pattern);
	if (!proc)
	{
		*exit_code = 2;
		return (SHELL_EXIT);
	}
	if (prepare_arg(env, &proc, shell) == FAIL)
	{
		free(proc);
		*exit_code = 2;
		return (SHELL_EXIT);
	}
	tokens = ft_split(proc, ' ');
	free(proc);
	return (check_exit_tokens(tokens, exit_code));
}

int	exit_shell(char *pattern, t_command *command, t_shell *shell)
{
	int	exit_code;
	int	ret;

	(void)command;
	if (pattern)
	{
		ret = handle_exit_arg(pattern, command->env_list, &exit_code, shell);
		if (ret != -1)
		{
			shell->exit_status = exit_code;
			return (ret);
		}
	}
	else
	{
		exit_code = shell->exit_status;
	}
	shell->exit_status = exit_code;
	return (SHELL_EXIT);
}
