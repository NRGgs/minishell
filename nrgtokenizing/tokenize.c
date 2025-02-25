#include "../includes/libft/libft.h"
#include "../includes/minishell.h"
#include "token.h"


void	skip_spaces(char **s)
{
	while (**s == ' '
		|| **s == '\f'
		|| **s == '\r'
		|| **s == '\n'
		|| **s == '\t'
		|| **s == '\v')
		(*s)++;
}

bool	skip_escapes(char *s, size_t *len, bool escaped)
{
	if (s[*len] != '\\')
		return (false);
	while (s[*len] == '\\')
	{
		escaped = !escaped;
		(*len)++;
	}
	return (escaped);
}

bool	is_delimiter(char *s, bool escaped)
{
	if (*s == ' '
		|| *s == '\0'
		|| *s == '\f'
		|| *s == '\r'
		|| *s == '\n'
		|| *s == '\t'
		|| *s == '\v')
		return (true);
	if (!escaped
		&& (ft_strncmp(s, "<<", 2) == 0
		|| ft_strncmp(s, ">>", 2) == 0
		|| *s == '|'
		|| *s == '<'
		|| *s == '>'))
		return (true);
	return (false);
}

size_t	quote_length(char *str, size_t len)
{
	char	quote;

	quote = str[len++];
	while (str[len] != '\0' && str[len] != quote)
		len++;
	return (len);
}

size_t	length_redirect(char *str)
{
	if (ft_strncmp(str, "<<", 2) == 0
		|| ft_strncmp(str, ">>", 2) == 0)
		return (2);
	return (1);
}

size_t	next_word_length(char *str)
{
	size_t	len;
	bool	escaped;

	len = 0;
	escaped = false;
	while (str[len] != '\0')
	{
		escaped = skip_escapes(str, &len, escaped);
		if (is_delimiter(str + len, escaped))
		{
			if (len == 0)
				return (length_redirect(str));
			return (len);
		}
		if ((str[len] == '\'' || str[len] == '\"') && !escaped)
			len = quote_length(str, len);
		len++;
	}
	return (len);
}

int	get_word(char **str, char **word)
{
	size_t	len;

	skip_spaces(str);
	len = next_word_length(*str);
	*word = malloc(sizeof(char) * (len + 1));
	if (*word == NULL)
		return (FAIL);
	ft_strlcpy(*word, *str, len + 1);
	*str += len;
	return (SUCCESS);
}

int	create_token(char **str, t_token **tokens)
{
	t_token			*token;
	char			*word;

	if (get_word(str, &word) == FAIL)
		return (FAIL);
	token = token_new(word, E_NONE);
	if (token == NULL)
		return (FAIL);
	token_add_back(tokens, token);
	return (SUCCESS);
}

bool	is_redirect(char *s)
{
	if (ft_strncmp(s, "<<", 2) == 0
		|| ft_strncmp(s, ">>", 2) == 0
		|| *s == '<'
		|| *s == '>')
		return (true);
	return (false);
}

bool	is_option(char *s)
{
	if (*s == '-')
		return (true);
	return (false);
}

void	give_token_types(t_token **tokens)
{
	t_token	*current;

	current = *tokens;
	while (current != NULL)
	{
		if (current->type == E_NONE)
		{
			if (current == *tokens && !is_redirect(current->token))
				current->type = E_COMMAND;
			else if (is_redirect(current->token))
				current->type = E_REDIRECTION;
			else if (ft_strcmp(current->token, "|") == 0)
				current->type = E_PIPE;
			else if (previous_token(*tokens, current)->type == E_REDIRECTION)
				current->type = E_FILENAME;
			else if (previous_token(*tokens, current)->type == E_PIPE)
				current->type = E_COMMAND;
			else if (is_option(current->token))
				current->type = E_OPTION;
			else
				current->type = E_ARGUMENT;
		}
		current = current->next;
	}
}

t_token	*tokenize(char *str)
{
	t_token		*tokens;
	char		*start;

	tokens = NULL;
	start = str;
	while (*str != '\0')
	{
		if (create_token(&str, &tokens) == FAIL)
		{
			clean_tokens(&tokens);
			free(start);
			return (NULL);
		}
	}
	give_token_types(&tokens);
	free(start);
	return (tokens);
}















// int	get_command(t_command **cmd, char **str)
// {
// 	char	*token;
// 	int		token_type;

// 	token_type = get_token(str, &token);
// 	if (token_type == TOKEN_ERROR)
// 		return (FAIL);
// 	if (token_type == COMMAND)
// 		(*cmd)->command = token;
// 	if (token_type == OPTION)
// 		(*cmd)->options = token;
// 	if (token_type == PATTERN)
// 		(*cmd)->pattern = token;
// 	if (token_type == REDIRECTION)
// 		set_redirection(cmd, token);
// 	return (SUCCESS);
// }

// int	create_command(char **str, t_command **commands)
// {
// 	t_command	*cmd;

// 	cmd = cmd_new(NULL, NULL);
// 	if (cmd == NULL)
// 		return (FAIL);
// 	if (get_command(&cmd, str) == FAIL)
// 	{
// 		clean_commands(&cmd);
// 		return (FAIL);
// 	}
// 	cmd_add_back(commands, cmd);
// 	return (SUCCESS);
// }