#include "execution/exec.h"
#include "lexer/parce.h"

int     main(int ac, char **av, char **envp)
 {
         (void) ac;
         (void) av;
 
         t_env   *env;
         t_lexer lexer;
         char    *input;
         t_cmd   *head;
	 int	last_status;
 
         head = NULL;
         env = init_env_list(envp);
         while (1)
         {
                 input = readline("\e[0;32mminishell$ \e[0m");
                 if (!input)
                 {
                         free(input);
                         //free t_env
                         break ;
                 }
                 add_history(input);
                 if (!find_error(lexer, input))
                 {
                         lexer = lexer_new(input);
                         head = build_cmd_list(&lexer, env);
                         if (head)
			 {
			 	last_status = run_command(head, &env);
				free_cmds(head);
				status_set(last_status);
			 }
                 }
                 free(input);
         }
	 return (last_status);
 }

/*int main(int ac, char **av, char **envp)
{
    (void)ac;
    (void)av;

    t_env   *env = init_env_list(envp);
    t_lexer lexer;
    t_cmd   *head;
    char    *input;
    int     last_status = 0;

    head = NULL;

    if (!isatty(STDIN_FILENO))  // ✅ Non-interactive
    {
        // Read whole stdin into one string
        size_t size = 0;
        char *buffer = NULL;
        char tmp[4096];
        ssize_t r;

        while ((r = read(STDIN_FILENO, tmp, sizeof(tmp) - 1)) > 0)
        {
            tmp[r] = '\0';
            char *old = buffer;
            buffer = ft_strjoin(old ? old : "", tmp);
            free(old);
        }

        if (buffer && *buffer)
        {
            if (!find_error(lexer, buffer))
            {
                lexer = lexer_new(buffer);
                head = build_cmd_list(&lexer, env);
                if (head)
                {
                    last_status = run_command(head, &env);
                    free_cmds(head);
                    status_set(last_status);
                }
            }
        }
        free(buffer);
        return last_status;
    }

    // ✅ Interactive shell
    while (1)
    {
        input = readline("minishell$ ");
        if (!input)
            break;

        add_history(input);
        if (!find_error(lexer, input))
        {
            lexer = lexer_new(input);
            head = build_cmd_list(&lexer, env);
            if (head)
            {
                last_status = run_command(head, &env);
                free_cmds(head);
                status_set(last_status);
            }
        }
        free(input);
    }
    return last_status;
}*/

