#include "../exec.h"

void	env_add_back(t_env **env, t_env *new)
{
	t_env	*tmp;

	if (!*env)
	{
		*env = new;
		return ;
	}
	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_env	*env_new(char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

t_env	*init_env_list(char **envp)
{
	t_env	*env;
	t_env	*new;
	char	*equal_sign;
	char	*key;
	char	*value;

	env = NULL;
	while (*envp)
	{
		equal_sign = ft_strchr(*envp, '=');
		if (!equal_sign)
		{
			envp++;
			continue ;
		}
		key = ft_substr(*envp, 0, equal_sign - *envp);
		value = ft_strdup(equal_sign + 1);
		new = env_new(key, value);
		env_add_back(&env, new);
		envp++;
	}
	return (env);
}
