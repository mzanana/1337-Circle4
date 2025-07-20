#include "exec.h"

char	*ft_strjoing_free(char *s1, char *s2)
{
	char	*joined;
	int	len1;
	int	len2;
	int	i;
	int	j;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	joined = malloc(len1 + len2 + 1);
	if (!joined)
	{
		free(s1);
		return (NULL);
	}
	i = 0;
	while (s1[i])
	{
		joined[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		joined[i++] = s2[j++];
	joined[i] = '\0';
	free(s1);
	return (joined);
}

void	ft_free_split(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	*get_env_value(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	*find_cmd_path(char *cmd, t_env *env)
{
	char	*path_value;
	char	**paths;
	char	*full_path;
	int	i;

	if (!cmd)
		return (NULL);
	path_value = get_env_value(env, "PATH");
	if (!path_value || ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	paths = ft_split(path_value, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], "/");
		if (!full_path)
		{
			ft_free_split(paths);
			return (NULL);
		}
		full_path = ft_strjoing_free(full_path, cmd);
		if (!full_path)
		{
			ft_free_split(paths);
			return (NULL);
		}
		if (access(full_path, X_OK) == 0)
		{
			ft_free_split(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	ft_free_split(paths);
	return (NULL);
}

/*int	main(int ac, char **av, char **envp)
{
	(void)ac;
	char	*path;

	t_env	*env = init_env_list(envp);
	path = find_cmd_path(av[1], env);
	if (path)
	{
		printf("Path: %s\n", path);
		free(path);
	}
	else
		printf("Command not found\n");
	return (0);
}*/
