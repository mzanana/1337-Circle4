/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaamaja <anaamaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 00:20:48 by anaamaja          #+#    #+#             */
/*   Updated: 2025/08/22 00:20:49 by anaamaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing_hf.h"

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
