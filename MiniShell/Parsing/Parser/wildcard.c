#include "../parsing_hf.h"

// void	asterisk_or_args(char *arg, t_cmd *cmd)
// {
// 	if (arg && ft_strchr(arg, '*'))
// 	{
// 		if (!join_current_dir(cmd, arg))
// 			add_to_argv(cmd, arg);
// 		else
// 			free(arg);
// 	}
// 	else if (arg)
// 		add_to_argv(cmd, arg);
// }

// int	asterisk_in_filename(char *target, t_cmd *cmd, t_token *tok)
// {
// 	char	*ast_tar;

// 	ast_tar = join_current_dir_redi(target);
// 	if (ast_tar)
// 		add_redirection(cmd, type_redir(tok), ast_tar);
// 	else
// 	{
// 		g_herdoc_stop = true;
// 		write(2, "wild_card error\n", 16);
// 	}
// 	return (1);
// }

char	*get_single_file_or_null(char *patern)
{
	DIR				*dir_files;
	struct dirent	*dir;
	char			*filename;

	dir_files = opendir(".");
	filename = NULL;
	while (dir_files)
	{
		dir = readdir(dir_files);
		if (!dir)
			break ;
		if (dir->d_name[0] == '.' && patern[0] != '.')
			continue ;
		if (wildcmp(dir->d_name, patern))
		{
			if (filename)
				return (closedir(dir_files), NULL);
			filename = dir->d_name;
		}
	}
	if (filename)
		filename = ft_strjoin(filename, "");
	else
		filename = ft_strdup(patern);
	return (closedir(dir_files), filename);
}

char	*join_current_dir_redi(char *patern)
{
	char	*new_target;

	new_target = get_single_file_or_null(patern);
	// free(patern);
	return (new_target);
}

char	*ft_strstr(char *str, char *little, size_t z)
{
	size_t	i;
	size_t	j;

	if (*little == '\0')
		return (str);
	i = 0;
	while (str && str[i])
	{
		j = 0;
		while (little && str[i + j] == little[j] && j < z)
			j++;
		if (j == z)
			return (&str[i]);
		i++;
	}
	return (NULL);
}

bool	ends_with_substr(char *str, char *end, size_t i)
{
	if (ft_strlen(str) < i)
		return (false);
	while (str && *str)
		str++;
	str--;
	while (i > 0)
	{
		i--;
		if (*str != end[i])
			return (false);
		str--;
	}
	return (true);
}

bool	_wildcmp_help(char *str, char *pattern)
{
	size_t	sz;

	while (*pattern)
	{
		while (*pattern == '*')
		{
			if (!*(++pattern))
				return (true);
		}
		sz = 0;
		while (pattern[sz] != '*' && pattern[sz])
			sz++;
		if (sz > 0 && !pattern[sz])
			return (ends_with_substr(str, pattern, sz));
		str = ft_strstr(str, pattern, sz);
		if (!str)
			return (false);
		pattern += sz;
		str += sz;
	}
	return (true);
}

bool	wildcmp(char *str, char *pattern)
{
	while (*pattern && *pattern != '*')
	{
		if (*str != *pattern)
			return (false);
		str++;
		pattern++;
	}
	if (!*pattern && *str)
		return (false);
	return (_wildcmp_help(str, pattern));
}

bool	join_current_dir(t_cmd *cmd, char *patern)
{
	DIR				*dir_files;
	struct dirent	*dir;
	bool			added;

	dir_files = opendir(".");
	added = false;
	if (!dir_files)
	{
		write(2, "Error while opening the directory\n", 34);
		return (false);
	}
	while (dir_files)
	{
		dir = readdir(dir_files);
		if (!dir)
			break ;
		if (dir->d_name[0] == '.' && patern[0] != '.')
			continue ;
		if (wildcmp(dir->d_name, patern))
		{
            cmd_argv_fill(cmd, ft_strdup2(dir->d_name));
			added = true;
		}
	}
	return (closedir(dir_files), added);
}