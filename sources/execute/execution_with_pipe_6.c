/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_with_pipe_6.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:33:51 by iriadyns          #+#    #+#             */
/*   Updated: 2025/03/24 18:19:27 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	process_here_doc(t_command *current, t_shell *shell)
{
	int		fd;
	char	*filename;

	filename = create_heredoc_file(current->pattern, current->env_list, shell);
	if (!filename)
		exit(1);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		free(filename);
		exit(1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		free(filename);
		exit(1);
	}
	close(fd);
	unlink(filename);
	free(filename);
}

void	execute_command_pipe(t_command *current, char *path, t_shell *shell)
{
	process_redir_or_exit(current, shell);
	if (current->in_type == HERE_DOC)
		process_here_doc(current, shell);
	if (is_builtin(current->command))
		handle_builtin_pipe(&current, path, shell);
	else
		handle_external_pipe(&current, path, shell);
}

int	count_tokens(char **arr)
{
	int	cnt;

	cnt = 0;
	while (arr && arr[cnt])
		cnt++;
	return (cnt);
}
