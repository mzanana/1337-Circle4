
#include "exec.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Very naive ft_split by a single char
char **split_simple(char *line, char sep)
{
    int i = 0, j = 0, k = 0;
    int count = 2; // estimate (line + NULL)
    while (line && line[i])
        if (line[i++] == sep)
            count++;
    char **res = malloc(sizeof(char *) * count);
    if (!res)
        return (NULL);
    i = 0;
    while (line[i])
    {
        while (line[i] == sep)
            i++;
        int start = i;
        while (line[i] && line[i] != sep)
            i++;
        int len = i - start;
        if (len > 0)
        {
            res[j] = malloc(len + 1);
            if (!res[j])
                return (NULL);
            strncpy(res[j], &line[start], len);
            res[j][len] = '\0';
            j++;
        }
    }
    res[j] = NULL;
    return (res);
}

t_cmd *create_cmd_node(char *segment)
{
    t_cmd *cmd = malloc(sizeof(t_cmd));
    if (!cmd)
        return (NULL);
    cmd->redir = NULL;
    cmd->next = NULL;

    // naive redirection detection
    char *redir_out = strstr(segment, ">");
    if (redir_out)
    {
        *redir_out = '\0';
        redir_out++;
        while (*redir_out == ' ')
            redir_out++;
        cmd->redir = new_redir(R_OUTPUT, redir_out);
    }

    cmd->argv = ft_split(segment, ' ');
    return (cmd);
}

t_cmd *parse_to_cmds(char *input)
{
    char **segments = split_simple(input, '|');
    if (!segments)
        return (NULL);
    t_cmd *head = NULL, *cur = NULL;
    for (int i = 0; segments[i]; i++)
    {
        t_cmd *node = create_cmd_node(segments[i]);
        if (!head)
            head = node;
        else
            cur->next = node;
        cur = node;
    }
    for (int i = 0; segments[i]; i++)
        free(segments[i]);
    free(segments);
    return (head);
}

void free_cmds(t_cmd *cmd)
{
    while (cmd)
    {
        t_cmd *next = cmd->next;
        ft_free_split(cmd->argv);
        if (cmd->redir)
        {
            free(cmd->redir->filename);
            free(cmd->redir);
        }
        free(cmd);
        cmd = next;
    }
}

int _main(int ac, char **av, char **envp)
{
    (void)ac;
    (void)av;
    char *line;
    int last_status = 0;

    t_env *env = init_env_list(envp);
    while ((line = readline("minishell> ")))
    {
        if (*line)
            add_history(line);
        t_cmd *cmds = parse_to_cmds(line);
        if (cmds)
            run_command(cmds, &env);
        free_cmds(cmds);
        free(line);
    }
    free_env_list(env);
    return (last_status);
}
