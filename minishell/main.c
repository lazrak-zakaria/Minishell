#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_yassir 	ys;

	ys.env = env;
	ys.exit_status = 0;
	ys.list_cmd = NULL;
	char *a = readline(">");
	ft_parse(a, &ys);
	
	// gcc main.c ft_part_1.c ft_part_2.c ft_part_3.c ft_part_3_5.c  ft_part_4.c ft_part_5.c vector.c queue.c ft_parse.c -lreadline 
	printf ("----------------------------------------------------------\n\n");
}
