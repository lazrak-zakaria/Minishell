#include "minishell.h"


/*************/

t_list	*ft_lstlast(t_list *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (!lst)
		return ;
	if (!(*lst))
		*lst = new;
	else
	{
		temp = ft_lstlast(*lst);
		temp->next = new;
	}
}

void	ft_p(char **a);

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = (t_list *)malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->data = content;
	node->next = NULL;
	return (node);
}


/******************/
void	ft_free_q(t_queue *q)
{
	t_queue	 *te = q;
	while (q)
	{
		free (q->data);
		free (q);
		q = te->next;
	}
}

void	ft_print_queue(t_queue *q)
{
	while (q)
	{
		printf ("%s  ", q->data);
		q = q->next;
	}
	printf ("\n");
}

void	ft_print_ele(t_queue *q)
{
	t_elem *tr ;
	while (q)
	{
		tr = q->data;
		char *a = tr->s;

		printf ("%s  \n", a);
		q = q->next;
	}
}

char	*ft_substr(char	*a, int s, int e)
{
	char	*answer;
	int		k;
	answer = malloc (sizeof (char) * (e - s + 1));
	k = 0;
	while (s < e && a[s])
		answer[k++] = a[s++];
	answer[k] = '\0';
	//printf ("%s\n", answer);
	return (answer);
}

char	**ft_cp(t_queue *q)
{
	char **answer;

	answer = malloc (sizeof(char *) * (ft_q_size(q) + 1));
	int i = 0;
	while (q)
	{
		answer[i++] = strdup(q->data);
		q = q->next;
	}
	answer[i] = NULL;
	return answer;
}

t_list	*ft_copy_(t_queue *q)
{
	t_list			*cmd;
	t_cmd_parse 	*from;
	t_cmd_package 	*to;

	cmd = NULL;
	while (q)
	{
		to = malloc(sizeof(t_cmd_package));
		from = q->data;
		to->cmd = ft_cp(from->cmd);
		to->outfile = ft_cp(from->outfile);
		to->infile = ft_cp(from->infile);
		to->rel_1 = ft_cp(from->rel_1);
		to->rel_2 = ft_cp(from->rel_2);
		to->fd_0 = 0;
		to->fd_1 = 1;
		ft_lstadd_back(&cmd, ft_lstnew(to));
		q = q->next;
	}
	return cmd;
}
void	ft_print2d(char **a)
{
	int i = 0;
	while (a[i])
		printf ("%s 	|", a[i++]);
	printf ("\n");
}
int	main(int ac, char **av, char **env)
{
	t_queue	*q = NULL;
	t_yassir 	ys;

	ys.env = env;
	ys.exit_status = 255;
	//char *a = "\"'cmd -l'\" '|' \"'$USER'\" cm<d < ok >> inf|ile << her>edoc > outfile | cm|d3";
	//char	*a= "''cmd -l | << ''h echo \"ok\" | cmd2 -a>>ap>out|cmd3|cmd4 $???";
	char *a = readline(">");
	q = ft_part_1(a);
	q = ft_part_2(q);
	q = ft_part_3(q);
	ft_part_3_5(q);
	q = ft_part_4(q, &ys);
	q = ft_part_5(q);


	ys.list_cmd = ft_copy_(q);
	t_list 	*y = ys.list_cmd;
	while (y)
	{
		ft_print2d(y->data->cmd);
		ft_print2d(y->data->outfile);
		ft_print2d(y->data->rel_1);
		ft_print2d(y->data->infile);
		ft_print2d(y->data->rel_2);
		printf ("\n----------------------------------------------------------\n\n");
		y = y->next;
	}
	//t_queue *ww = q;
	// while (ww)
	// {
	// 	t_cmd_parse	*e = ww->data;
	// 	printf ("cmd 		:  ");
	// 	ft_print_queue(e->cmd);
	// 	printf ("outfile 	:  ");
	// 	ft_print_queue(e->outfile);
	// 	printf ("rel_1 		:  ");
	// 	ft_print_queue(e->rel_1);
	// 	printf ("infile		:  ");
	// 	ft_print_queue(e->infile);
	// 	printf ("rel_2 		:  ");
	// 	ft_print_queue(e->rel_2);
	// 	printf ("\n\n");
	// 	ww = ww->next;
	// }
//	system ("leaks a.out");
	printf ("----------------------------------------------------------\n\n");


}
