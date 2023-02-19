#include "minishell.h"

t_queue	*ft_part_4(t_queue *queue)
{
	t_queue		*queue_answer = NULL;
	t_queue		*temp;
	int			i;
	char		*a;
	int			f;
	t_vector	vec;
	char		c;

	while (queue)
	{
		temp = ft_pop(&queue);
		a = temp->data;
		i = 0;
		f = 0;
		t_elem	*tt = malloc (sizeof(t_elem) * 1);
		tt->s = 0;
		tt->quote += (a[0] == '\'' || a[0] == '"');
		ft_create_vector(&vec, 20);
		while (a[i])
		{
			if (a[i] == '\'' || a[i] == '\"')
			{
				c = a[i++];
				while (a[i] && a[i] != c)
					ft_push_back(&vec, a[i++]);
				if (!a[i])
					break ;
				i++;
			}
			else
				ft_push_back(&vec, a[i++]);
		}
		tt->s = vec.string;
		ft_push(&queue_answer, ft_new_node(tt));
	}
	t_queue *q = queue_answer;
	while (q)
	{
		printf("%s\n", ((t_elem*)q->data)->s);
		//printf("quote ----->  %d\n", ((t_elem*)q->data)->quote);
		q = q->next;
	}

	return (queue_answer);
}
