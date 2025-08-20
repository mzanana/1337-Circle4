#include "../exec.h"

int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (ft_strlen(str) == 0)
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(char **argv, int last_status)
{
	int	code;

	if (isatty(STDIN_FILENO))
		write(1, "exit\n", 5);
	if (!argv[1])
		exit(last_status);
	if (!is_numeric(argv[1]))
	{
		log_err("minishell: exit: numeric argument required\n");
		exit(2);
	}
	if (argv[2])
	{
		log_err("minishell: exit: too many arguments\n");
		return (1);
	}
	code = ft_atoi(argv[1]);
	exit(code % 256);
}
