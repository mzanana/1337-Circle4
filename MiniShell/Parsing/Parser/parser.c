#include "../parsing_hf.h"

int	count_args(t_cmd *cmd)
{
	int ret;

	if (!cmd->argv)
		return (0);
	ret = 0;
	while (cmd->argv[ret])
		ret++;
	return ret;
}

void	cmd_argv_fill(t_cmd *cmd, char *value)
{
	char	**new_argv;
	int		length;
	int		i;

	length = count_args(cmd);
	new_argv = gc_calloc(sizeof(char*) * (length + 2));
	if (!new_argv)
		return ;
	if (cmd->argv)
	{
		i = -1;
		while (cmd->argv[++i])
			new_argv[i] = cmd->argv[i];
	}
	new_argv[length] = value;
	new_argv[length + 1] = NULL;
	cmd->argv = NULL;
	cmd->argv = new_argv;
}

t_redir	*redir_maker(t_token_type type, char *value, bool is_quoted)
{
	t_redir	*ret;

	ret = gc_calloc (sizeof (t_redir));
	ret->type = type;
	ret->filename = value;
	ret->quoted = is_quoted;
	ret->next = NULL;
	return (ret);
}

void	cmd_redir_fill(t_redir **redir, t_token_type type, char * value, bool is_quoted)
{
	t_redir	*curr;
	t_redir	*holder;
	
	if (!*redir)
	{
		*redir = redir_maker(type, value, is_quoted);
		return ;
	}
	curr = *redir;
	while (curr->next)
		curr = curr->next;
	holder = redir_maker(type, value, is_quoted);
	curr->next = holder;
	return ;
}
void cmd_add_back(t_cmd **head, t_cmd *new)
{
	t_cmd *tmp;
	
	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return ;
}

char	*remove_qoutes_if_needed(char *s, bool *quoted)
{
	char	*res;
	char	qoute;
	int	i;
	int	j;

	i = 0;
	j = 0;
	res = gc_calloc(ft_strlen(s) + 1);
	if (!res || !s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
		{
			qoute = s[i++];
			*quoted = true;
			while (s[i] &&s[i] != qoute)
				res[j++] = s[i++];
			if (s[i] == qoute)
				i++;
		}
		else
			res[j++] = s[i++];
	}
	res[j] = '\0';
	return (res);
}
t_cmd *tokens_to_commands(t_token *tokens)
{
	t_cmd	*ret;
	t_cmd	*tmp;
	char	*heredoc_del;
	bool	is_quoted;
	
	ret = NULL;
	while (tokens)
	{
		tmp = gc_calloc(sizeof(t_cmd));
		while (tokens && tokens->type != T_PIPE)
		{
			if (tokens->type == T_WORD)
			{
				if (!tokens->is_quoted && ft_strchr(tokens->value, '*'))
				{
					if (!join_current_dir(tmp, tokens->value))
						cmd_argv_fill(tmp, tokens->value);					
				}
				else
					cmd_argv_fill(tmp, tokens->value);
				tokens = tokens->next;
			}
			else
			{
				is_quoted = false;
				heredoc_del = tokens->next->value;
				if (tokens->type == T_HEREDOC)
					heredoc_del = remove_qoutes_if_needed(heredoc_del, &is_quoted);
				if (!tokens->is_quoted && ft_strchr(heredoc_del, '*'))
				{
					char *tes = join_current_dir_redi(heredoc_del);
					if (tes)
						cmd_redir_fill(&(tmp->redir), tokens->type, tes, tokens->next->is_quoted);					
					else
						write (1, "bash: ambiguous redirect\n", 25);
				}
				else
					cmd_redir_fill(&(tmp->redir), tokens->type, heredoc_del, tokens->next->is_quoted);
				tokens = tokens->next->next;
			}
		}
		cmd_add_back(&ret, tmp);
		if (tokens && tokens->type == T_PIPE)
			tokens = tokens->next;
	}
	return (ret);
}





void print_parsed_commands(t_cmd *cmds)
{
    t_cmd *cmd;
    int i;
    t_redir *r;

    cmd = cmds;
    int cmd_index = 1;
    while (cmd)
    {
        printf("=== Command %d ===\n", cmd_index++);
        // Print argv
        i = 0;
        if (cmd->argv)
        {
            printf("argv: ");
            while (cmd->argv[i])
            {
                printf("[%s] ", cmd->argv[i]);
                i++;
            }
            printf("\n");// parser.c
        }
        else
            printf("argv: (empty)\n");

        // Print redirections
        r = cmd->redir;
        while (r)
        {
            printf("redir: type=%d file=[%s] quoted=%d\n", r->type, r->filename, r->quoted);
            r = r->next;
        }
        cmd = cmd->next;
    }
}