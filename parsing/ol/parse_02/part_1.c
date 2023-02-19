#include "minishell.h"
#include "vector.h"


t_queue	*ft_part_1(char *a)
{
	t_queue	*queue_answer;
	t_vector	vec;
	int		i;
	char	c;
	int		f;

	queue_answer = NULL;
	i = 0;
	ft_create_vector(&vec, 20);
	f = 0;
	while (a[i])
	{
		if (a[i] == ' ')
		{
			if (f)
			{
				ft_push(&queue_answer, ft_new_node(vec.string));
				ft_create_vector(&vec, 20);
				f = 0;
			}
			i++;
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
				ft_push_back(&vec, a[i++]);
			if (!a[i])
				ft_push(&queue_answer, ft_new_node(vec.string));
		}
	}
	t_queue *q = queue_answer;
	while (q)
	{
		printf("%s\n", q->data);
		q = q->next;
	}
	return (queue_answer);
}

/*
this part to handle spaces
*/