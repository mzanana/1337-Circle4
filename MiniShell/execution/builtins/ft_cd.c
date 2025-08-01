#include "../exec.h"
void log_err(char *msg)
{
	write(2, msg, ft_strlen(msg));
}

int	ft_cd(char **argv)
{
	if (!argv[1])
	{
		log_err("bash: cd : missing argument\n");
		return (1);
	}
	if (argv[2])
	{
		log_err("bash: cd: too many arguments\n");
		return (1);
	}
	if (chdir(argv[1]) != 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}
