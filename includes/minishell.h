/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: iriadyns <iriadyns@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/10 11:59:51 by nmattos-      #+#    #+#                 */
/*   Updated: 2025/03/30 13:06:48 by nmattos       ########   odam.nl         */
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
# define IS_DIRECTORY 126
# define CMD_NOT_FOUND 127
# define SIGINT_CANCELLATION 130
# define ILLEGAL_INSTRUCTION 132
# define ILLEGAL_DIVISION 133
# define FAILED_ASSERTION 134
# define INT_OVERFLOW 136
# define MEMORY_OVERFLOW 137
# define UNALIGNED_MEM_ACCESS 138
# define SEG_FAULT 139

/* Singly linked list. Stores all environments. */
typedef struct s_env
{
	char				*name;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct s_shell
{
	int					exit_status;
	t_env				*env_list;
}						t_shell;

typedef struct s_redirect
{
	int					type;
	bool				is_input;
	char				*arg;
	struct s_redirect	*next;
}	t_redirect;

/* Singly linked list. Stores all commands. */
typedef struct s_command
{
	char				*command;
	char				*options;
	char				*pattern;
	t_redirect			*redirect;
	struct s_command	*next;
	struct s_env		*env_list;
}						t_command;

/* Enum for token types */
typedef enum e_token_type
{
	E_NONE,
	E_COMMAND,
	E_OPTION,
	E_ARGUMENT,
	E_REDIRECTION,
	E_PIPE,
	E_FILENAME
}	t_token_type;

/* Singly linked list. Stores all tokens */
typedef struct s_token
{
	char			*token;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

typedef struct s_exec_data
{
	int					pipe_in;
	int					*pipe_fd;
	char				*path;
	t_shell				*shell;
}						t_exec_data;

typedef struct s_child_data
{
	t_command			*current;
	int					*pipe_in;
	int					pipe_fd[2];
	char				*path;
	t_shell				*shell;
}						t_child_data;

typedef struct s_exec_context
{
	char	*path;
	t_shell	*shell;
}	t_exec_context;

/*****************************************************************************\
*                             Function Prototypes                             *
\*****************************************************************************/

/* signal.c */
void		check_signals(void);
void		signal_heredoc(int signum);
void		set_error(char *error_msg, int error_code);
void		command_handler(int signum);

/* --------------- Parse --------------------------------------------------- */

/* parse.c */
t_command	*parse_input(char *input);

/* parse_utils.c */
bool		valid_char(char c);
char		*read_till_quotes(char delimiter, char **pattern);

/* assign.c */
int			assign_token(t_command **cmd, t_token **tokens, t_token **current);

/* get_commands.c */
t_command	*get_commands(t_token *tokens);

/* heredoc.c */
int			here_doc_redirection(char *delimiter, t_command **last);
int			restore_stdin(int stdin_backup, char **input);
char		*create_heredoc_file(char *input, t_env *env_list, t_shell *shell);

/* --------------- Tokenize ------------------------------------------------ */

/* tokenize */
t_token		*tokenize(char *str);

/* word_length.c */
size_t		next_word_length(char *str);
size_t		quote_length(char *str, size_t len);

/* utils.c */
void		skip_spaces(char **s);
bool		skip_escapes(char *s, size_t *len, bool escaped);
bool		is_delimiter(char *s, bool escaped);
bool		is_redirect(char *s);
bool		is_option(char *s);

/* --------------- Expand -------------------------------------------------- */

/* prepare */
int			prepare_arg(t_env *env_list, char **arg, t_shell *shell);
int			handle_variables(t_env *env_list, char **arg, t_shell *shell);

/* variables */
char		*replace_var(char *str, char *var_ptr, \
				t_env *env_list, t_shell *shell);
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

/* --------------- Memory -------------------------------------------------- */

/* commands.c */
t_command	*cmd_new(char *command, char *options);
t_command	*cmd_last(t_command *cmds);
void		cmd_add_back(t_command **cmds, t_command *new_cmd);

/* tokens.c */
t_token		*token_new(char *word, t_token_type type);
void		token_add_back(t_token **tokens, t_token *new);
t_token		*prev_token(t_token *tokens, t_token *current);
void		clean_tokens(t_token **tokens);


/* redirects.c */
t_redirect	*new_redirect(int type, bool is_input, char *arg);
t_redirect	*redirect_last(t_redirect *node);
void		add_redirect(t_redirect **head, t_redirect *new);


/* free.c */
void		free_null(void **ptr);
void		clean_2d_array(char **array);
void		cmd_clear(t_command **cmd);
void		clean_commands(t_command **cmds);

/* --------------- Execute ------------------------------------------------- */

/* builtins.c */
int			is_builtin(char *command);
int			handle_cd(t_command *command, t_shell *shell);
int			execute_builtin(t_command **cmd_list, t_shell *shell);
void		free_args(char **args);

/* find_path.c */
char		*true_path(char *argv, t_env *env_list, t_shell *shell);
char		*path_finder(char **env);
char		*find_path(char *command, t_env *env_list, t_shell *shell);
void		fn_path(char **res_split, char *argv);
void		free_2d_array(char **arr);

/* find_path_2.c */
char		*search_in_paths(char **res_split, char **args, \
				t_shell *shell, char *argv);
char		**split_paths_env(t_env *env_list);
char		**split_args_with_prepare(char *argv, t_env *env_list, \
				t_shell *shell);
char		*check_argv_executable(char *argv, t_shell *shell);
void		f_error(t_shell *shell, char *command);

/* execution.c */
int			execute_commands(t_command *commands, t_shell *shell);
t_env		*create_env_node(const char *name, const char *value);
int			count_tokens(char **arr);

/* execution_without_pipe */
void		handle_child_process(t_command *commands, char *path,
				char *args[], t_shell *shell);
void		execute_command(t_command *commands, char *path,
				char *args[], t_shell *shell);
int			exec_external_no_pipe(t_command *commands, t_shell *shell);
int			exec_builtin_no_pipe(t_command *commands, t_shell *shell);
void		restore_fds(int in, int out);

/* execution_without_pipe_2 */
int			execution_without_pipe(t_command *commands, t_shell *shell);

/* execution_with_pipe_1.c */
char		**get_command_args(t_command *current);
void		setup_input_output(t_command *current, int pipe_in,
				int *pipe_fd);
void		execute_command_pipe(t_command *current, char *path,
				t_shell *shell);
void		wait_for_children(void);

/* execution_with_pipe_2.c */
void		handle_child(t_command *current, t_exec_data *exec_data);
void		handle_parent(int *pipe_fd, int *pipe_in);
int			execution_with_pipe(t_command *commands, t_shell *shell);
int			setup_pipe(int *pipe_fd);

/* execution_with_pipe_3.c */
int			process_single_command(t_command *current, int *pipe_in,
				t_shell *shell);
void		parent_branch(t_command *current, int *pipe_in, int pipe_fd[2]);
void		child_branch(t_child_data *child);
int			setup_pipe_if_needed(t_command *current, int pipe_fd[2]);
char		*handle_double_spaces(const char *str);
void		handle_builtin_pipe(t_command **cmd_ptr, char *path,
				t_shell *shell);
void		process_redir_or_exit(t_command *current, t_shell *shell);
void		handle_external_pipe(t_command **cmd_ptr,
				char *path, t_shell *shell);

/* cd.c */
int			change_pwd(t_env *env_list);
int			cd_home(t_env *env_list);
int			cd(t_env *env_list, t_command *command, t_shell *shell);
int			check_option(char *argv);

/* pwd.c */
int			pwd(char **argv);

/* echo.c */
int			echo(t_command *command, t_shell *shell);
int			process_echo_options(char **args, int *start_index);
char		*join_tokens(char **tokens, int start_index);
void		free_split(char **split);
char		*join_with_space(char *s1, char *s2);
int			compute_total_length(char **tokens, int start_index);

/* export.c */
t_env		*find_env_var(t_env *env_list, const char *name);
t_env		*create_env_var(t_env **env_list, const char *name,
				const char *value);
void		print_exported_vars(t_env *env_list);
int			my_export(t_env **env_list, char **args, t_shell *shell);
int			run_export_builtin(t_command *command, t_shell *shell);

/* export_2.c */
void		add_env_to_list(t_env **env_list, t_env *new_var);
t_env		*alloc_env_node(const char *name, const char *value);
void		handle_export_equal(t_env **env_list, char *arg,
				char *equal_sign);
void		handle_export_no_equal(t_env **env_list, char *arg);
void		process_export_arg(t_env **env_list, char *arg, t_shell *shell);

/* export_3.c */
bool		valid_export_arg(char *arg, t_shell *shell);

/* unset.c */
int			my_unset(t_env **env_list, char **args);
int			remove_env_var(t_env **env_list, const char *var_name);
int			run_unset_builtin(t_command *command, t_shell *shell);

/* exit.c */
int			exit_shell(char *pattern, t_command *command, t_shell *shell);

/* env.c */
int			env(t_env *env_list);

/* redirect.c */
int			handle_input_redirection(t_command *cmd, t_shell *shell);
int			handle_output_redirection(t_command *cmd, t_shell *shell);
int			process_redirections(t_command *cmd, t_shell *shell);

/* init_env_list.c */
int			parse_env_var(char *env_str, char **name, char **value);
void		append_env_node(t_env **list, t_env *new_node);
t_env		*init_env_list(void);
void		clear_env_list(t_env *env_list);

/* build_execve_args.c */
char		**build_execve_args(t_command *cmd, t_shell *shell);
int			is_all_whitespace(const char *str);
char		**special_split(char const *s, char c);
char		**fill_tokens(const char *s, char c,
				int token_count);
void		handle_special_commands_in_structure(t_command *cmd,
				t_env *env_list, t_shell *shell);
char		*get_env_value(t_env *env_list, char *name);
int			handle_dollar_commands(t_command *cmd, t_shell *shell);
int			prepare_path_and_pipe(t_command *current,
				int *pipe_fd, t_shell *shell, char **path);
int			fork_error_cleanup(t_command *current, char *path, int pipe_fd[2]);
void		fill_child_data(t_child_data *child_data, t_command *current,
				int pipe_fd[2], t_shell *shell);

#endif
