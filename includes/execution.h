/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 16:53:15 by iriadyns          #+#    #+#             */
/*   Updated: 2024/12/10 12:05:26 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>

# define PIPE 1

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
} t_env;


typedef struct s_command
{
	char				*command;	// command
	char				*options;	// options, NULL
	int					in_type;	// FILE, PIPE, STDIN, HERE_DOC
	int					out_type;	// FILE, PIPE, STDOUT
	char				*input;		// filename, here_doc_string, NULL
	char				*output;	// filename, NULL
	struct s_command	*next;
	t_env				*env_list;
}	t_command;

// builtins
int	is_builtin(char *command);
int	execute_builtin(t_command *command);

// find_path
char *true_path(char *argv, char **env);
char *path_finder(char **env);
char *find_path(char *command, char **env);
void f_error(void);

// execution
void	execute_commands(t_command *commands);
void	execution_without_pipe(t_command *commands);
void execution_with_pipe(t_command *commands);

// cd
int	change_pwd(t_env *env_list);
int	cd_home(t_env *env_list);
int cd(t_env *env_list, char **argv);
t_env *get_env(t_env *env_list, char *identifier);
int	check_option(char *argv);

// pwd
int		pwd(char **argv);

// echo
int		echo(char **argv);
int		check_echo_option(char *option);

// export
int my_export(t_env *env_list, char *var);

// unset
int unset(t_env *env_list, char *var);

// exit
int exit_shell(char *input);

// env
int	env(void);

#endif
