/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlazrak <zlazrak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:16:52 by zlazrak           #+#    #+#             */
/*   Updated: 2023/02/21 10:29:39 by zlazrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_here(t_queue *queue, t_prompt *ys);
int	check_enclosed_quotes(char	*a);
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
		te = q->next;
		free (q->data);
		free (q);
		q = te;
	}
}
void	ft_free_qq(t_queue *q)
{
	t_queue	 *te = q;
	t_elem	*e;
	while (q)
	{
		te = q->next;
		e = q->data;
		free (e->s);
		free (e);
		free (q);
		q = te;
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
		to->file = ft_cp(from->file);
		to->rel = ft_cp(from->rel);
		/*    */
		to->buffer = ft_cp(from->buffer);
		/*     */
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
		printf ("|%d|%s|" , a[0][0],a[i++]);
	printf ("\n");
}

void	ft_free(t_queue *q)
{
	t_queue	*qq;
	while (q)
	{
		qq = q->next;
		free(q);
		q = qq;
	}
}
void	ft_free_part_5(t_queue *q)
{
	t_cmd_parse	*p;
	t_queue		*qq;

	while (q)
	{
		qq = q->next;
		p = q->data;
	//	ft_free_q(p->cmd);
		ft_free(p->cmd);
		ft_free(p->file);
		ft_free_q(p->rel); //later free buffer;
		free(p);
	
		free(q);
		//printf ("here\n");
		q = qq;
	}
}

void	ft_parse(char *a, t_prompt *ys)
{
	t_queue	*q;
	t_queue	*temp;

	if (check_enclosed_quotes(a))
	{
		ft_putstr_fd("unclosed quotes\n", 2);
		ys->exit_status = 258;
		return ;
	}
	q = ft_part_1(a);
	
	temp = ft_part_2(q);

	ft_free_q(q);

	q = ft_part_3(temp);
	
	ft_free_q(temp);
	if(ft_part_3_5(q))
	{
		ft_free_q(q);
		ys->exit_status = 258;
		//system("leaks a.out");
		return ;
	};

	temp = ft_part_4(q, ys);
		ft_free_q(q);
	q = ft_part_5(temp);
	ft_here(q, ys);
	ys->list_cmd = ft_copy_(q);

	// t_list 	*y = ys->list_cmd;
	// while (y)
	// {
	// 	printf ("cmd 		:  ");
	// 	ft_print2d(y->data->cmd);
	// 	printf ("outfile 	:  ");
	// 	ft_print2d(y->data->outfile);
	// 	printf ("rel_1 		:  ");
	// 	ft_print2d(y->data->rel_1);
	// 		printf ("infile		:  ");
	// 	ft_print2d(y->data->infile);
	// 	printf ("rel_2 		:  ");
	// 	ft_print2d(y->data->rel_2);
	// 	printf ("\n----------------------------------------------------------\n\n");
	// 	y = y->next;
	// }
		ft_free_qq(temp);
	//ft_print_ele(temp);
		ft_free_part_5(q);
	//system("leaks a.out");
}
