#include "../includes/libft/libft.h"
#include "../includes/minishell.h"
#include "token.h"

t_token	*token_new(char *word, t_token_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->token = word;
	token->type = type;
	token->next = NULL;
	return (token);
}

void	token_add_back(t_token **tokens, t_token *new)
{
	t_token	*current;

	if (*tokens == NULL)
	{
		*tokens = new;
		return ;
	}
	current = *tokens;
	while (current->next != NULL)
		current = current->next;
	current->next = new;
}

t_token	*previous_token(t_token *tokens, t_token *current)
{
	t_token	*previous;

	previous = tokens;
	while (previous->next != current)
		previous = previous->next;
	if (previous == current)
		return (NULL);
	return (previous);
}

void	clean_tokens(t_token **tokens)
{
	t_token	*current;
	t_token	*next;

	if (tokens == NULL || *tokens == NULL)
		return;
	current = *tokens;
	while (current != NULL)
	{
		next = current->next;
		if (current->token != NULL)
			free(current->token);
		current->token = NULL;
		current->type = E_NONE;
		free(current);
		current = next;
	}
	*tokens = NULL;
}
