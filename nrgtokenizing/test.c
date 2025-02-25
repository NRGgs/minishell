#include "../includes/libft/libft.h"
#include "token.h"

void	test_stuff(char *cmd);

int main()
{
	test_stuff("echo Hello World");
	test_stuff("echo abc | piped");
	test_stuff("echo abc |piped");
	test_stuff("echo abc| piped");
	test_stuff("echo abc \\|piped | piped");
	test_stuff("echo abc \\\\|piped | piped");
	test_stuff("echo <<HEREDOCTEST");
	test_stuff("echo <<HEREDOCTEST | piped");
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
}

void	test_stuff(char *cmd)
{
	char *str = ft_strdup(cmd);
	t_token *tokens = tokenize(str);
	t_token *current = tokens;
	while (current != NULL)
	{
		printf("[%s] ", current->token);
		current = current->next;
	}
	printf("\n");
	clean_tokens(&tokens);
}
