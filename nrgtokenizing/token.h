#ifndef TOKEN_H
# define TOKEN_H


#define FAIL 0
#define SUCCESS 1

// typedef struct s_command
// {
// 	char				*command;
// 	char				*options;
// 	char				*pattern;
// 	int					in_type;
// 	int					out_type;
// 	char				*input;
// 	char				*output;
// 	struct s_command	*next;
// 	struct s_env		*env_list;
// }						t_command;

typedef enum e_token_type
{
	TOKEN_ERROR,
	COMMAND,
	OPTION,
	PATTERN,
	REDIRECTION,
}	t_token_type;


char	**tokenize(char *str);

#endif