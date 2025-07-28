#include "../parsing_hf.h"

char    *ft_strndup(char *str, size_t n)
{
        size_t  i;
        char    *dup;

        i = 0;
        while (str[i] && i < n)
                i++;
        dup = gc_calloc(sizeof(char) * (i + 1));
        if (!dup)
                return (NULL);
        i = 0;
        while (str[i] && i < n)
        {
                dup[i] = str[i];
                i++;
        }
        dup[i] = '\0';
        return (dup);
}

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

t_token	*token_new(char *value, t_token_type type)
{
	t_token	*token;

	token = gc_calloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = value;
	token->type = type;
	token->next = NULL;
	return (token);
}

void	token_add_back(t_token **head, t_token *new)
{
	t_token	*last;

	if (!head || !new)
		return ;
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	last = *head;
	while (last->next != NULL)
		last = last->next;
	last->next = new;
}

