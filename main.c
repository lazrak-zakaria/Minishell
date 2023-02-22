#include "minishell.h"

void	ft_memfree(char **a)
{
	int i = 0;
	while (a && a[i])
	{
		free (a[i]);
		i++;
	}
	free (a);
}
void	ft_free_lis(t_list *head)
{
	t_list *tt;
	t_cmd_package *p;
	while (head)
	{
		tt = head->next;
		p = head->data;
		ft_memfree(p->cmd);
		ft_memfree(p->file);
		ft_memfree(p->rel);
		ft_memfree(p->buffer);
		free (p);
		free (head);
		head = tt;
	}
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_prompt 	prompt;

	prompt.s_env = ft_creat_env(env); //		linked list
	prompt.env = get_env(prompt.s_env); // 		char ** alocated
	prompt.exit_status = 0;
	prompt.list_cmd = NULL;

	while(1)
	{
		prompt.list_cmd = NULL;
		char *a = readline("-->");
		if (a == NULL)
			exit(0);
		ft_parse(a, &prompt);
		free(a);

	/******************************/
		t_list *oo = prompt.list_cmd;
		ft_exec(&prompt);
		ft_free_lis(oo);

	}
}
