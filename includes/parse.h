/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmattos- <nmattos-@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/01 10:44:28 by nmattos       #+#    #+#                 */
/*   Updated: 2024/12/13 10:38:36 by nmattos       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "libft/libft.h"
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

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

/* Singly linked list. Stores all commands */
typedef struct s_command
{
	char				*command;	// command
	char				*options;	// options, NULL
	int					in_type;	// FILE, PIPE, STDIN, HERE_DOC
	int					out_type;	// FILE, PIPE, STDOUT
	char				*input;		// filename, here_doc_string, NULL
	char				*output;	// filename, NULL
	struct s_command	*next;
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
int	textfile_redirection(char *filename, char *redirection, t_command **last);
int	here_doc_redirection(char *delimiter, t_command **last);
int	string_redirection(char **input, t_command **last, int *i);

/* parse_clean.c */
void	clean_2d_array(char **array);
void	clean_variables(t_variable **vars);
void	clean_commands(t_command **cmds);

#endif
