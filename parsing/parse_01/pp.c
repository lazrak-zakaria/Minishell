#include "minishell.h"
#include "queue.h"
#include "vector.c"
#include <readline/readline.h>
#include <readline/history.h>

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

int	ft_strlen(char *a)
{
	int i = 0;
	while (a[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *a, char *b)
{
	char	*answer;
	int i = -1;
	answer = malloc(sizeof (char) * (ft_strlen(a) + ft_strlen(b) + 1));
	while (a[++i])
		answer[i] = a[i];
	while (*b)
		answer[i++] = *b++;
	answer[i] = 0;
	return answer;
}

t_queue		*ft_part1(char	*a)
{
	t_queue	*queue;
	int		i;
	char	c;
	int		j;
	int		f;

	f = 0;
	queue = NULL;
	i = 0;
	while (a[i])
	{
		if (a[i] == ' ')
		{
			i++;
			continue;
		}
		else
		{
			j = i;
			while (a[i])
			{
				if (a[i] == ' ' && !f)
					break;
				if ((a[i] == '\'' || a[i] == '\"') && !f)
					f = 1;
				else if ((a[i] == '\'' || a[i] == '\"') && f)
					f = 0;
				i++;
			}
			ft_push(&queue, ft_new_node(ft_substr(a, j, i)));
		}
	}
	t_queue *q = queue;
	while (q)
	{
		printf("%s\n", q->data);
		q = q->next;
	}
	return (queue);
}

t_queue	*ft_part2(t_queue *queue)
{
	t_queue *queue_answer = NULL;
	t_queue	*temp;
	char	*a;
	int		i;
	char	c;
	int		f = 0;


	while (queue)
	{
		i = 0;
		temp = ft_pop(&queue);
		a = (char*)temp->data;
		while (a[i])
		{
			if (a[i] == '|')
			{
				ft_push(&queue_answer, ft_new_node(ft_substr(a, i, i + 1)));
				i++;
			}
			else
			{
				int	j = i;
				while (a[i])
				{
					if (a[i] == '|' && !f)
						break ;
					if ((a[i] == '\'' || a[i] == '\"') && !f)
						f = 1;
					else if ((a[i] == '\'' || a[i] == '\"') && f )
						f = 0;
					i++;
				}
				ft_push(&queue_answer, ft_new_node(ft_substr(a, j, i)));
			}
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

t_queue	*ft_part3(t_queue *queue)
{
	t_queue *queue_answer = NULL;
	t_queue	*temp;
	char	*a;
	int		f = 0;

	while (queue)
	{
		temp = ft_pop(&queue);
		a = temp->data;
		int i = 0;
		while (a[i])
		{
			if (a[i] == '<' || a[i] == '>')
			{
				ft_push(&queue_answer, ft_new_node(ft_substr(a, i, i + 1)));
				i++;
			}
			else
			{
				int j = i;
				while (a[i])
				{
					if ((a[i] == '>' || a[i] == '<') && !f)
						break;
					if ((a[i] == '\'' || a[i] == '\"') && !f)
						f = 1;
					else if ((a[i] == '\"' || a[i] == '\'') && f)
						f = 0;
					i++;
				}
				ft_push(&queue_answer, ft_new_node(ft_substr(a, j, i)));
			}
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

t_queue		*ft_part4(t_queue *queue)
{
	t_queue		*queue_answer = NULL;
	t_queue		*temp;
	int			i = 0;
	char		*a;
	int 		f = 0;
	t_vector	vec;
	char 		c;
	int k = 0;

	while (queue)
	{//printf ("hiiiiii\n");
		temp = ft_pop(&queue);
		a = temp->data;
		ft_create_vector(&vec, 100);
		i = 0;
		int j = 0;
		while (a[i])
		{
			if ((a[i] == '\'' || a[i] == '\"'))
			{
				c = a[i++];
				while (a[i] && a[i] != c)
				{
					ft_push_back(&vec, a[i]);
					i++;
				}
				if (a[i])
					i++;
			}
			else
				ft_push_back(&vec, a[i++]);
		}
		//int yy = 0;
		ft_push(&queue_answer, ft_new_node(vec.string));
	}
	t_queue *q = queue_answer;
	while (q)
	{
		printf("%s\n", q->data);
		q = q->next;
	}
	return (queue_answer);


};

t_queue	*ft_part5(t_queue *queue)
{
	t_queue	*temp;
	t_queue	*queue_answer = NULL;
	char	*a;
	//if bash: syntax error near unexpected token `|'
	//   | ls | wc |ls        ls | | wc ls
		int  j = 0;
		t_cmd_wrapper *cmd ;
		cmd = malloc (sizeof (*cmd));
		memset(cmd, 0, sizeof(*cmd));
	while (queue)
	{
		temp = ft_pop(&queue); 
		a = temp->data;
		int i = 0;
		if ((a[i] == '|' && !a[i + 1]))
		{
			j = 0;
			ft_push(&queue_answer, ft_new_node(cmd));
			cmd = malloc (sizeof (*cmd));
			memset(cmd, 0, sizeof(*cmd));
		}
		else if (a[i] == '<' && !a[i + 1])
		{
			temp = ft_pop(&queue); 
			a = temp->data;
			cmd->infile = a;
		}
		else if (a[i] == '>' && !a[i + 1])
		{
			temp = ft_pop(&queue); 
			a = temp->data;
			cmd->outfile = a;
		}
		else if (!j)
		{
			cmd->cmd = a;
			j = 1;
		}
		else if (j)
		{
			ft_push(&cmd->args, ft_new_node(a));
		}
	}
	ft_push(&queue_answer, ft_new_node(cmd));

	t_queue *q = queue_answer;
	while (q)
	{
		printf ("--------------------------------------------------\n\n");
		t_cmd_wrapper *aa = q->data;
		printf ("cmd = %s\n", aa->cmd);
		printf ("out = %s\n", aa->outfile);
		printf ("in  =%s\n", aa->infile);
		t_queue *qq = aa->args;
		while (qq)
		{
			printf ("%s ", qq->data);
			qq = qq->next;
		}
		printf ("\n--------------------------------------------------\n\n");
		q = q->next;
	}
	return (queue_answer);
}

int main()
{
	// char *a = "\"<\" cat\"|\" \"main  .c\"|wc|ls>\"'la'\"|ls|wc";
	//char *a = "<\"main.c\" cat | ls -l > ok";
	//char *a = "< ls cat \"main.c\"|\"echo\" hello > ls ";
	
	
	t_queue	*queue = ft_part1(a);
	
	printf ("**************************\n\n\n\n");
	
	queue = ft_part2(queue);
	
	printf ("**************************\n\n\n\n");

	queue = ft_part3(queue);
	
	printf ("**************************\n\n\n\n");

	queue = ft_part4(queue);

	printf ("************************** 55 \n\n\n\n");

	t_queue *cmds = ft_part5(queue);



	return (0);
}