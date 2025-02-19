#include "../includes/libft/libft.h"
#define FAIL 0
#define SUCCESS 1

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

typedef enum e_token_type
{
	TOKEN_ERROR,
	COMMAND,
	OPTION,
	PATTERN,
	REDIRECTION,
}	t_token_type;





int	get_command(t_command **cmd, char **str)
{
	char	*token;
	int		token_type;

	token_type = get_token(str, &token);
	if (token_type == TOKEN_ERROR)
		return (FAIL);
	if (token_type == COMMAND)
		(*cmd)->command = token;
	if (token_type == OPTION)
		(*cmd)->options = token;
	if (token_type == PATTERN)
		(*cmd)->pattern = token;
	if (token_type == REDIRECTION)
		set_redirection(cmd, token);
	return (SUCCESS);
}

int	create_command(char **str, t_command **commands)
{
	t_command	*cmd;

	cmd = cmd_new(NULL, NULL);
	if (cmd == NULL)
		return (FAIL);
	if (get_command(&cmd, str) == FAIL)
	{
		clean_commands(&cmd);
		return (FAIL);
	}
	cmd_add_back(commands, cmd);
	return (SUCCESS);
}

char	**tokenize(char *str)
{
	t_command	*commands;
	size_t		nth_token;

	nth_token = 0;
	while (str != '\0')
	{
		if (create_command(&str, &commands) == FAIL)
		{
			clean_commands(&commands);
			free(str);
			return (NULL);
		}
	}
	free(str);
	return (commands);
}
