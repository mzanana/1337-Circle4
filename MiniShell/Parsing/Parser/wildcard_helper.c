#include "../parsing_hf.h"

char	*join_current_dir_redi(char *patern)
{
	char	*new_target;

	new_target = get_single_file_or_null(patern);
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
