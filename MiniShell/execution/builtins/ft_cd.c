#include "../exec.h"

int	ft_cd(char **argv)
{
	if (!argv[1])
	{
		write(2, "bash: cd : missing argument\n", 28);
		return (1);
	}
	if (argv[2])
	{
		write(2, "bash: cd: too many arguments\n", 30);
		return (1);
	}
	if (chdir(argv[1]) != 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}

void	print_curr_dir(void)
{
	char	*cwd = getcwd(NULL, 0);

	if (cwd)
	{
		printf("Current directory : %s\n", cwd);
		free(cwd);
	}
}

int main(void)
{
	char **cmd1 = ft_split("cd tkherbi9a", ' ');
	char **cmd2 = ft_split("cd joj args", ' ');
	char **cmd3 = ft_split("cd ./khdam", ' ');
	char **cmd4 = ft_split("cd ..", ' ');

	ft_cd(cmd1);
	print_curr_dir();
	ft_cd(cmd2);
	print_curr_dir();
	ft_cd(cmd3);
	print_curr_dir();
	ft_cd(cmd4);
	print_curr_dir();

}
