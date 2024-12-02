/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 10:44:28 by nmattos           #+#    #+#             */
/*   Updated: 2024/12/02 10:39:11 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "libft/libft.h"
# include <stdbool.h>
# include <stdio.h>

/* Return Values */
# define FAIL 0
# define SUCCESS 1

/* In/Out Types */
# define FILE 0
# define PIPE 1
# define STDIN 2
# define STDOUT 3
# define HERE_DOC 4

/* Singly linked list. Stores all commands */
typedef struct s_command
{
	char		*command;	// command
	char		*options;	// options, NULL
	int			in_type;	// FILE, PIPE, STDIN, HERE_DOC
	int			out_type;	// FILE, PIPE, STDOUT
	char		*input;		// filename, here_doc_string, NULL
	char		*output;	// filename, NULL
	t_command	*next;
}	t_command;

/*	Singly linked list. Stores all variables. */
typedef struct s_variable
{
	char		*name;
	char		*value;
	t_variable	*next;
}	t_variable;

/*****************************************************************************\
*                             Function Prototypes                             *
\*****************************************************************************/

/* parse.c */
bool	is_variable(char *str);
int		parse_variable(char *str, t_variable **vars);

/* variables.c */
t_variable	*var_new(char *name, char *value);
t_variable	*var_last(t_variable *vars);
void		var_add_back(t_variable **vars, t_variable *new_var);
t_variable	*var_find(t_variable *vars, char *name);

#endif
