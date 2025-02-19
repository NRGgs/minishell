#include "../includes/libft/libft.h"

void	test_stuff(char *cmd);

int main()
{
	test_stuff("echo \"Hello World\"");
	test_stuff("ls -l");
	test_stuff("cat -e -t -v file");
	test_stuff("echo \"Hello World\" | cat -e -t -v file");
	test_stuff("echo \"Hello World\" | cat -e -t -v file | wc -l");
	test_stuff("echo Hello World \"Testing    spaces\"");
	test_stuff("echo Hello World \"Testing   \'   quotes\"");
	test_stuff("echo Hello World \'Testing   \"   quotes\'");
}

void	test_stuff(char *cmd)
{
	char *str = ft_strdup(cmd);
	char **tokens = tokenize(str);
	int i = 0;
	while (tokens[i])
	{
		printf("%s\n", tokens[i]);
		i++;
	}
	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
	free(str);
}
