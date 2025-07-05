#ifndef EXEC_H
#define EXEC_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include "../libft/libft.h"

typedef enum s_redir_type
{
	R_INPUT,
	R_OUTPUT,
	R_APPAND,
	R_HEREDOC,
}	t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	char	*filename;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char	**argv;
	t_redir	*redir;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_env
{
	char	*key;
	char	*value;
	struct s_env	*next;
}	t_env;

/* builtins */
int	ft_echo(char **argv);
int	ft_pwd(void);
int	ft_env(char **argv, t_env *env);
int	ft_export(char **argv, t_env **env);
int	ft_unset(char **argv, t_env **env);


/* init_env_list */
void	env_add_back(t_env **env, t_env *new);
t_env	*env_new(char *key, char *value);
t_env	*init_env_list(char **envp);
int	ft_strcmp(char *s1, char *s2);

#endif
