#include "../../execution/exec.h"

char	*ft_substr2(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	index;

	if (!s || start > ft_strlen(s))
		return (ft_strdup(""));
	if ((len + start) < ft_strlen(s))
		ret = gc_calloc ((len + 1) * sizeof(char));
	else
		ret = gc_calloc ((ft_strlen(s) - start + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	index = 0;
	while (index < len && s[start])
		ret[index++] = s[start++];
	ret[index] = '\0';
	return (ret);
}

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}

int var_start(char c)
{
	return (ft_isalpha(c) || c == '_');
}

int var_middle(char c)
{
	return (ft_isalnum(c) || c == '_');
}