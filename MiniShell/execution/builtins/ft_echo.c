#include "../exec.h"

int	is_option_n(char *str)
{
	int	i;

	if (!str || str[0] != '-')
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(char **argv)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	while (argv[i] && is_option_n(argv[i]))
	{
		newline = 0;
		i++;
	}
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (1);
}

int	main()
{
	t_cmd	*cmd = malloc(sizeof(t_cmd));

	cmd->argv = ft_split("echo |", ' ');
	cmd->redir = NULL;
	cmd->next = NULL;
	ft_echo(cmd->argv);
}
