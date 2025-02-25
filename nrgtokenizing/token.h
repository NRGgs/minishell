#ifndef TOKEN_H
# define TOKEN_H

#define FAIL 0
#define SUCCESS 1

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

typedef struct s_token
{
	char			*token;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

t_token	*tokenize(char *str);
t_command	*get_commands(t_token *tokens);

t_token	*token_new(char *word, t_token_type type);
void	token_add_back(t_token **tokens, t_token *new);
t_token	*previous_token(t_token *tokens, t_token *current);
void	clean_tokens(t_token **tokens);

#endif