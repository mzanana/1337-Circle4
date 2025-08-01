#ifndef EXEC_H
#define EXEC_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include "../Libft/libft.h"
# include "../lexer/parce.h"

/*typedef enum s_redir_type
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
*/

/* builtins */
int	ft_echo(char **argv);
int	ft_pwd(void);
int	ft_env(char **argv, t_env *env);
int	ft_export(char **argv, t_env **env);
int	ft_unset(char **argv, t_env **env);
int	ft_exit(char **argv, int last_status);

/* init_env_list */
void	env_add_back(t_env **env, t_env *new);
t_env	*env_new(char *key, char *value);
t_env	*init_env_list(char **envp);
int	ft_strcmp(char *s1, char *s2);


int	handle_redirections(t_redir *redir);
char	*find_cmd_path(char *cmd, t_env *env);

int	is_builtin(char *cmd);
int	run_builtin(t_cmd *cmd, t_env **env);
int	is_single_builtin(t_cmd *cmd);
void	free_env_list(t_env *env);//temporary
void	ft_free_split(char **arr);
void	free_cmds(t_cmd *cmd);


int	ft_cd(char **argv);


int	status_get(void);
void	status_set(int value);

int	run_command(t_cmd *cmds, t_env **env);
char	**env_to_envp(t_env *env);
void	free_envp_array(char **envp);
t_redir	*new_redir(t_redir_type type, char *filename);
void	log_err(char *msg);
void	print_err(char *msg1, char *path, char *msg2);
#endif
