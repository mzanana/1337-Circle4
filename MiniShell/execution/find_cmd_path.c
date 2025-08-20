#include "exec.h"

char	*ft_strjoing_free(char *s1, char *s2)
{
	char	*joined;

	int (len1), (len2), (i), (j);
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

char	*search_in_paths(char **paths, char *cmd)
{
	int		i;
	char	*full_path;
	char	*tmp;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return (ft_free_split(paths), NULL);
		full_path = ft_strjoing_free(tmp, cmd);
		if (!full_path)
			return (ft_free_split(paths), NULL);
		if (access(full_path, X_OK) == 0)
			return (ft_free_split(paths), full_path);
		free(full_path);
		i++;
	}
	ft_free_split(paths);
	return (NULL);
}

char	*find_cmd_path(char *cmd, t_env *env)
{
	char	*path_value;
	char	**paths;

	if (!cmd)
		return (NULL);
	path_value = get_env_value(env, "PATH");
	if (!path_value || ft_strchr(cmd, '/') || ft_strlen(cmd) == 0)
		return (ft_strdup(cmd));
	paths = ft_split(path_value, ':');
	if (!paths)
		return (NULL);
	return (search_in_paths(paths, cmd));
}
