/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:59:51 by nmattos-          #+#    #+#             */
/*   Updated: 2025/02/24 12:31:56 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

# define SHELL_CONTINUE 0
# define SHELL_EXIT 1

# define REDIRECT_INPUT 1
# define REDIRECT_OUTPUT 2

# define AFTER 0
# define BEFORE 1

/* In Quotes */
# define FALSE 0
# define SINGLE 1
# define DOUBLE 2

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

/* Exit Statuses */
# define MINOR 1
# define MAJOR 2
# define CMD_NOT_FOUND 127
# define SIGINT_CANCELLATION 130
# define ILLEGAL_INSTRUCTION 132
# define ILLEGAL_DIVISION 133
# define FAILED_ASSERTION 134
# define INT_OVERFLOW 136
# define MEMORY_OVERFLOW 137
# define UNALIGNED_MEM_ACCESS 138
# define SEG_FAULT 139

extern int				g_exit_status;

/* Singly linked list. Stores all environments. */
typedef struct s_env
{
	char				*name;
	char				*value;
	struct s_env		*next;
}						t_env;

/* Singly linked list. Stores all commands. */
typedef struct s_command
{
	char				*command;
	char				*options;
	char				*pattern;
	int					in_type;
	int					out_type;
	char				*input;
	char				*output;
	struct s_command	*next;
	struct s_env		*env_list;
}						t_command;

/*	Singly linked list. Stores all variables. */
typedef struct s_variable
{
	char				*name;
	char				*value;
	struct s_variable	*next;
}						t_variable;

/*****************************************************************************\
*                             Function Prototypes                             *
\*****************************************************************************/

/* prepare */
int			prepare_arg(t_env *env_list, char **arg);

/* variables */
char		*replace_var(char *str, char *var_ptr, t_env *env_list);
bool		in_single_quotes(char *str, char *c);
bool		char_is_escaped(char *str, char *c);
char		*get_nth_var(char *str, int nth_var);

/* backslashes */
bool		check_quotes(char c, int *in_quotes, bool *escaped);
bool		back_backslash_handler(char **str, char **new_str,
				int *i, int *j);

/* quotes */
int			update_quotes(char c, char **new_str, int *j,
				int *in_quotes);
bool		quote_backslash_handler(char **str, char **new_str,
				int *i, int *j);

/* split */
char		**parse_split(char *s);

/* split_2 */
int			get_word_count(char *s);
char		**allocate_words(char *s, char **result);
char		**split_words(char *s, char **result);

/* split_utils */
int			parse_quote(char **s);
void		parse_quoted_string(char **s, char *result, int *i);
int			allocate_next_word(int *nth_word, int *length,
				char **result);

/* split_utils_2 */
void		skip_spaces(char **s);
int			is_escaped(char **s);
void		update_escape(bool *escaped, char c);
void		check_escapes(bool *escaped, char **s, int *length);

/* minishell.c */
void		set_error(char *error_msg, int error_code);

/* free.c */
void		free_null(void **ptr);

/* signal.c */
void		check_signals(void);
void		signal_heredoc(int signum);

/* parse.c */
t_command	*parse_user_input(char *input);

/* parse_checks.c */
bool		is_special(char *command);
bool		is_redirect(char *str);
int			is_command(char *cmd);
bool		options_possible(char *command);
int			check_path(char *cmd, char *path);

/* parse_split.c */
char		**parse_split(char *s);

/* parse_string.c */
int			parse_string(char **input, int *i, char **pattern,
				char quote);

/* parse_string_utils.c */
char		contains_quote(char *str);
int			n_chars_till_quote(char **input, int j, char quote);
char		*read_till_quotes(char delimiter, char **pattern);

/* parse_cmds.c */
int			parse_command(char **input, t_command **cmds, int *i);

/* commands.c */
t_command	*cmd_new(char *command, char *options);
t_command	*cmd_last(t_command *cmds);
void		cmd_add_back(t_command **cmds, t_command *new_cmd);

/* parse_var.c */
bool		is_variable(char *str);
bool		valid_char(char c);
int			parse_variable(char *str, t_variable **vars);
char		*replace_variable(char *str, t_variable *vars,
				char quote, t_command **commands);

/* variables.c */
t_variable	*var_new(char *name, char *value);
t_variable	*var_last(t_variable *vars);
void		var_add_back(t_variable **vars, t_variable *new_var);
t_variable	*var_find(t_variable *vars, char *name);

/* parse_redirect.c */
int			parse_redirect(char **input, t_command **cmds, int *i,
				int command_index);

/* redirections.c */
int			textfile_redirection(char *fn, char *redirect,
				t_command **last, int place);
int			string_redirection(char **input, t_command **last,
				int *i);

/* heredoc.c */
int			here_doc_redirection(char *delimiter, t_command **last);
int			restore_stdin(int stdin_backup, char **input);

/* parse_clean.c */
void		clean_2d_array(char **array);
void		clean_variables(t_variable **vars);
void		clean_commands(t_command **cmds);

/* builtins.c */
int			is_builtin(char *command);
int			handle_cd(t_command *command);
int			execute_builtin(t_command **cmd_list);
void		free_args(char **args);

/* find_path.c */
char		*true_path(char *argv, char **env);
char		*path_finder(char **env);
char		*find_path(char *command, char **env);
void		fn_path(char **res_split, char *argv);
void		free_2d_array(char **arr);

/* find_path_2.c */
char		*search_in_paths(char **res_split, char **args);
char		**split_args(char *argv);
char		**split_paths(char **env);
char		*check_argv_executable(char *argv);
void		f_error(void);

/* execution.c */
int			execute_commands(t_command *commands);
t_env		*create_env_node(const char *name, const char *value);
int			is_directory(const char *path);

/* execution_without_pipe */
void		handle_child_process(t_command *commands, char *path,
				char *args[]);
void		execute_command(t_command *commands, char *path,
				char *args[]);
int			exec_external_no_pipe(t_command *commands);
int			exec_builtin_no_pipe(t_command *commands);
void		restore_fds(int in, int out);

/* execution_without_pipe_2 */
int			execution_without_pipe(t_command *commands);

/* execution_with_pipe_1.c */
char		**get_command_args(t_command *current);
void		setup_input_output(t_command *current, int pipe_in,
				int *pipe_fd);
void		execute_command_pipe(t_command *current, char *path);
int			create_child_process(t_command *current, int pipe_in,
				int *pipe_fd, char *path);
void		wait_for_children(void);

/* execution_with_pipe_2.c */
void		handle_child(t_command *current, int pipe_in,
				int *pipe_fd, char *path);
void		handle_parent(int *pipe_fd, int *pipe_in);
int			execution_with_pipe(t_command *commands);
int			setup_pipe(int *pipe_fd);

/* execution_with_pipe_3.c */
int			process_single_command(t_command *current,
				int *pipe_in);

/* cd.c */
int			change_pwd(t_env *env_list);
int			cd_home(t_env *env_list);
int			cd(t_env *env_list, t_command *command);
t_env		*get_env(t_env *env_list, char *identifier);
int			check_option(char *argv);

/* pwd.c */
int			pwd(char **argv);

/* echo.c */
int			echo(t_command *command);

/* export.c */
t_env		*find_env_var(t_env *env_list, const char *name);
t_env		*create_env_var(t_env **env_list, const char *name,
				const char *value);
void		print_exported_vars(t_env *env_list);
int			my_export(t_env **env_list, char **args);
int			run_export_builtin(t_command *command);

/* export_2.c */
void		add_env_to_list(t_env **env_list, t_env *new_var);
t_env		*alloc_env_node(const char *name, const char *value);
void		handle_export_equal(t_env **env_list, char *arg,
				char *equal_sign);
void		handle_export_no_equal(t_env **env_list, char *arg);
void		process_export_arg(t_env **env_list, char *arg);

/* unset.c */
int			my_unset(t_env **env_list, char **args);
int			remove_env_var(t_env **env_list, const char *var_name);
char		**parse_args_for_unset(t_command *command);
int			run_unset_builtin(t_command *command);

/* exit.c */
int			exit_shell(char *pattern);

/* env.c */
int			env(t_env *env_list);

/* redirect.c */
int			handle_input_redirection(t_command *cmd);
int			handle_output_redirection(t_command *cmd);
int			process_redirections(t_command *cmd);

/* init_env_list.c */
int			parse_env_var(char *env_str, char **name, char **value);
void		append_env_node(t_env **list, t_env *new_node);
t_env		*init_env_list(void);
void		clear_env_list(t_env *env_list);

/* build_execve_args.c */
char		**build_execve_args(t_command *cmd);

#endif
