#include "../includes/libft/libft.h"
#include "token.h"

void	test_stuff(char *cmd);

int main()
{
	test_stuff("echo Hello World");
	test_stuff("echo abc | piped");
	test_stuff("echo abc |piped");
	test_stuff("echo abc| piped");
	test_stuff("echo abc\\| not_piped");
	test_stuff("echo abc\\\\| piped");
	test_stuff("echo abc \\|not_piped | piped");
	test_stuff("echo abc \\| piped | piped");
	test_stuff("echo abc \\\\|piped | piped");
	test_stuff("echo <<HEREDOCTEST");
	test_stuff("echo<<HEREDOCTEST | piped");
	test_stuff("echo $VAR");
	test_stuff("echo \\$VAR");
	test_stuff("echo hello > test.txt");
	test_stuff("echo hello >> test.txt");
	test_stuff("echo hello >>test.txt");
	test_stuff("echo hello>test.txt");

	test_stuff("echo \"Hello World\"");
	test_stuff("ls -l");
	test_stuff("cat -e -t -v file");
	test_stuff("echo \"Hello World\" | cat -e -t -v file");
	test_stuff("echo \"Hello World\" | cat -e -t -v file | wc -l");
	test_stuff("echo Hello World \"Testing    spaces\"");
	test_stuff("echo Hello World \"Testing   \'   quotes\"");
	test_stuff("echo Hello World \'Testing   \"   quotes\'");

	test_stuff("echo Hello World \\'Testing    \'my    quotes\'");
	test_stuff("< file");
}

void	print_tokentype(t_token_type type)
{
	if (type == E_NONE)
		printf("NONE\t\t");
	else if (type == E_TOKEN_ERROR)
		printf("TOKEN_ERROR\t\t");
	else if (type == E_COMMAND)
		printf("COMMAND\t\t");
	else if (type == E_OPTION)
		printf("OPTION\t");
	else if (type == E_ARGUMENT)
		printf("ARGUMENT\t");
	else if (type == E_REDIRECTION)
		printf("REDIRECTION\t");
	else if (type == E_FILENAME)
		printf("FILENAME\t");
	else if (type == E_PIPE)
		printf("PIPE\t\t");
}

void	test_stuff(char *cmd)
{
	char *str = ft_strdup(cmd);
	t_token *tokens = tokenize(str);
	t_token *current = tokens;
	while (current != NULL)
	{
		print_tokentype(current->type);
		printf("[%s]\n", current->token);
		current = current->next;
	}
	printf("\n");
	clean_tokens(&tokens);
}
