/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:59:51 by nmattos-          #+#    #+#             */
/*   Updated: 2024/12/20 13:00:39 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>

/* Return Values */
# define ERROR -1
# define FAIL 0
# define SUCCESS 1

/* In/Out Types */
# define TEXTFILE 0
# define HERE_DOC 1
# define APPEND 2
# define PIPE 3
# define STRING 4
# define STDIN 5
# define STDOUT 6
# define STD 7

/* Singly linked list. Stores all environments. */
typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
} t_env;

/* Singly linked list. Stores all commands. */
typedef struct s_command
{
	char				*command;
	char				*options;
	int					in_type;
	int					out_type;
	char				*input;
	char				*output;
	struct s_command	*next;
	struct s_env		*env_list;
}	t_command;

/*	Singly linked list. Stores all variables. */
typedef struct s_variable
{
	char				*name;
	char				*value;
	struct s_variable	*next;
}	t_variable;

/*****************************************************************************\
*                             Function Prototypes                             *
\*****************************************************************************/

/* signal.c */
void	check_signals(void);

/* parse.c */
t_command	*parse_user_input(char *input);

/* parse_cmds.c */
int		is_command(char *cmd);
int		parse_command(char **input, t_command **cmds, int *i);

/* commands.c */
t_command	*cmd_new(char *command, char *options);
t_command	*cmd_last(t_command *cmds);
void		cmd_add_back(t_command **cmds, t_command *new_cmd);

/* parse_var.c */
bool	is_variable(char *str);
int		parse_variable(char *str, t_variable **vars);
char	*replace_variable(char *str, t_variable *vars);

/* variables.c */
t_variable	*var_new(char *name, char *value);
t_variable	*var_last(t_variable *vars);
void		var_add_back(t_variable **vars, t_variable *new_var);
t_variable	*var_find(t_variable *vars, char *name);

/* parse_redirect.c */
int		parse_redirect(char **input, t_command **cmds, int *i, int command_index);

/* redirections.c */
int		textfile_redirection(char *filename, char *redirection, t_command **last);
int		here_doc_redirection(char *delimiter, t_command **last);
int		string_redirection(char **input, t_command **last, int *i);

/* parse_clean.c */
void	clean_2d_array(char **array);
void	clean_variables(t_variable **vars);
void	clean_commands(t_command **cmds);

/* builtins.c */
int		is_builtin(char *command);
int		execute_builtin(t_command *command);

/* find_path.c */
char 	*true_path(char *argv, char **env);
char 	*path_finder(char **env);
char 	*find_path(char *command, char **env);
void 	f_error(void);

/* execution.c */
void	execute_commands(t_command *commands);
void	execution_without_pipe(t_command *commands);
void 	execution_with_pipe(t_command *commands);

/* cd.c */
int		change_pwd(t_env *env_list);
int		cd_home(t_env *env_list);
int 	cd(t_env *env_list, char **argv);
t_env	*get_env(t_env *env_list, char *identifier);
int		check_option(char *argv);

/* pwd.c */
int		pwd(char **argv);

/* echo.c */
int		echo(char **argv);
int		check_echo_option(char *option);

/* export.c */
int		my_export(t_env *env_list, char *var);

/* unset.c */
int 	unset(t_env *env_list, char *var);

/* exit.c */
int 	exit_shell(char *input);

/* env.c */
int		env(void);

#endif
