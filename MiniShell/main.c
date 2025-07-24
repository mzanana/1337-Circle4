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
                 input = readline("JUST_TYPE# ");
                 if (!input)
                 {
                         write(1, "exit\n", 5);
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
				status_set(last_status);
			 }
                 }
                 free(input);
         }
	 return (last_status);
 }
