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













void	set_redirection(t_command **cmd, char *redirection)
{
	if (ft_strncmp(redirection, ">>", 2) == 0)
		(*cmd)->out_type = APPEND;
	else if (ft_strncmp(redirection, "<<", 2) == 0)
		(*cmd)->in_type = HERE_DOC;
	else if (redirection[0] == '>')
		(*cmd)->out_type = TEXTFILE;
	else if (redirection[0] == '<')
		(*cmd)->in_type = TEXTFILE;
}

int	set_filename(t_command **cmd, char *filename)
{
	char	*word;

	word = ft_strndup(filename, ft_strlen(filename));
	if (word == NULL)
		return (FAIL);
	if ((*cmd)->in_type == TEXTFILE)
		(*cmd)->input = word;
	else if ((*cmd)->out_type == TEXTFILE)
		(*cmd)->output = word;
	return (SUCCESS);
}

int	set_argument(char **arg, char *word)
{
	char	*temp;

	if (*arg == NULL)
	{
		*arg = word;
		return (SUCCESS);
	}
	temp = ft_strjoin(*arg, " ");
	if (temp == NULL)
		return (FAIL);
	free(*arg);
	*arg = temp;
	temp = ft_strjoin(*arg, word);
	if (temp == NULL)
		return (FAIL);
	*arg = temp;
	return (SUCCESS);
}

int	allocate_and_assign(t_command **cmd, t_token **tokens)
{
	char	*word;

	word = ft_strndup((*tokens)->token, ft_strlen((*tokens)->token));
	if (word == NULL)
		return (FAIL);
	if ((*tokens)->type == E_COMMAND)
		(*cmd)->command = word;
	else if ((*tokens)->type == E_OPTION)
	{
		if (set_argument(&(*cmd)->options, word) == FAIL)
			return (free(word), FAIL);
	}
	else if ((*tokens)->type == E_ARGUMENT)
		if (set_argument(&(*cmd)->pattern, word) == FAIL)
			return (free(word), FAIL);
	return (SUCCESS);
}

int	assign_token(t_command **cmd, t_token **tokens)
{
	if ((*tokens)->type == E_COMMAND
		|| (*tokens)->type == E_OPTION
		|| (*tokens)->type == E_ARGUMENT)
	{
		if (allocate_and_assign(cmd, tokens) == FAIL)
			return (FAIL);
	}
	else if ((*tokens)->type == E_REDIRECTION)
		set_redirection(cmd, (*tokens)->token);
	else if ((*tokens)->type == E_FILENAME)
	{
		if (set_filename(cmd, (*tokens)->token) == FAIL)
			return (FAIL);
	}
	return (SUCCESS);
}

int	fill_command(t_command **cmd, t_token **tokens)
{
	size_t	assignments;

	assignments = 0;
	while ((*tokens) != NULL)
	{
		if ((*tokens)->type == E_PIPE)
		{
			if (assignments > 0)
			{
				(*cmd)->out_type = PIPE;
				return (SUCCESS);
			}
			(*cmd)->in_type = PIPE;
		}
		else
		{
			if (assign_token(cmd, tokens) == FAIL)
				return (FAIL);
		}
		*tokens = (*tokens)->next;
		assignments++;
	}
	return (SUCCESS);
}

int	create_command(t_command **commands, t_token **tokens)
{
	t_command	*cmd;

	cmd = cmd_new(NULL, NULL);
	if (cmd == NULL)
		return (FAIL);
	if (fill_command(&cmd, tokens) == FAIL)
	{
		clean_commands(commands);
		return (FAIL);
	}
	cmd_add_back(commands, cmd);
	return (SUCCESS);
}

t_command	*get_commands(t_token *tokens)
{
	t_command	*commands;
	t_token		*current;

	commands = NULL;
	current = tokens;
	while (current != NULL)
	{
		if (create_command(&commands, &current) == FAIL)
		{
			clean_commands(&commands);
			return (NULL);
		}
	}
	return (commands);
}
















t_command	*parse_input(char *input)
{
	t_token	*tokens;
	t_command	*commands;

	tokens = tokenize(input);
	if (tokens == NULL)
		return (NULL);
	commands = get_commands(tokens);
	clean_tokens(&tokens);
	return (commands);
}
