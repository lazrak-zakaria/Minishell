#include "minishell.h"

t_queue	*ft_part_3(t_queue *queue)
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
		ft_create_vector(&vec, 20);
		while (a[i])
		{		
			if (a[i] == '<' || a[i] == '>')
			{
				if (f)
				{
					ft_push(&queue_answer, ft_new_node(vec.string));
					ft_create_vector(&vec, 20);
					f = 0;
				}
				c = a[i];
				while(a[i] == '>' || a[i] == '<') //(a[i] == c)  //a[i] == '>' || a[i] == '<'
					ft_push_back(&vec, a[i++]);
				ft_push(&queue_answer, ft_new_node(vec.string));
				ft_create_vector(&vec, 20);
				continue;
			}
			else
			{
				f = 1;
				if (a[i] == '\'' || a[i] == '\"')
				{
					c = a[i];
					ft_push_back(&vec, a[i++]);
					while (a[i] && a[i] != c)
						ft_push_back(&vec, a[i++]);
					ft_push_back(&vec, a[i++]);
				}
				else if (a[i])
				{	
					ft_push_back(&vec, a[i++]);
				}
				if (!a[i])
					ft_push(&queue_answer, ft_new_node(vec.string));
			}
		}
	}
	// t_queue *q = queue_answer;
	// while (q)
	// {
	// 	printf("%s\n", q->data);
	// 	q = q->next;
	// }

	return queue_answer;
}
