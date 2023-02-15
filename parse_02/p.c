#include "minishell.h"
#include "vector.h"

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

int		ft_is_token(char *a)
{
	if (a[0] == '<')
		return (1);
	if (a[0] == '>')
		return (1);
	return 0;
}
// void	ft_token_err(t_queue *q, char *a)
// {
// 	if (!q->next)
// 	{
// 		printf ("syntax error near unexpected token `newline'\n");
// 		exit(1);
// 	}
// 	if (a[0] == '>' && a[1] == '>' && a[2])
// 	{
// 		printf ("bash: syntax error near unexpected token `%s'\n", a+2);
// 	}
// 	if (a[0] == '<' && a[1] == '<' && a[2])
// 	{
// 		printf ("bash: syntax error near unexpected token `%s'\n", a+2);
// 	}
// 	if (a[0] == '<' && a[1] == '<' && a[2])
// 	{
// 		printf ("bash: syntax error near unexpected token `%s'\n", a+2);
// 	}
// }

t_queue	*ft_part_5(t_queue *queue)
{
	t_queue		*queue_answer = NULL;
	t_queue		*temp;
	int			i;
	char		*a;
	int			first;
	t_vector	vec;
	char		c;
	t_cmd_wrapper	*cmd;

	first = 1;
		cmd = malloc(sizeof(*cmd));
		memset(cmd, 0, sizeof(*cmd));
	while (queue)
	{
		temp = ft_pop(&queue);
		t_elem	*tt = temp->data;
		char	*a = tt->s;
		i = 0;
		if (a[i] == '|' && !a[i + 1])
		{
			ft_push(&queue_answer, ft_new_node(cmd));
			cmd = malloc(sizeof(*cmd));
			memset(cmd, 0, sizeof(*cmd));
			first = 1;
			continue;
		}
		if (ft_is_token(a))
		{
				//	printf ("+++++++++++++++++++++++++++++++++++++\n");
			if (a[i] == '<' && a[i+ 1] == '<')
			{
				if (tt->quote && first)
				{
					cmd->cmd = a;
				}
				else if (tt->quote && !first)
					ft_push(&cmd->args, ft_new_node(a));
				else
				{
					t_queue *yy = ft_pop(&queue);
					cmd->limiter = ((t_elem*)yy->data)->s;
				}
			}
			else if (a[i] == '<' && a[i + 1] == '\0')
			{
				if (tt->quote && first)
				{
					cmd->cmd = a;
				}
				else if (tt->quote && !first)
					ft_push(&cmd->args, ft_new_node(a));
				else
				{
					t_queue *yy = ft_pop(&queue);
					cmd->infile = ((t_elem*)yy->data)->s;
				}
			}
			else if (a[i] == '>' && a[i + 1] == '\0')
			{
				if (tt->quote && first)
				{
					cmd->cmd = a;
				}
				else if (tt->quote && !first)
					ft_push(&cmd->args, ft_new_node(a));
				else
				{
					t_queue *yy = ft_pop(&queue);
					cmd->outfile = ((t_elem*)yy->data)->s;
				}
			}
			else if (a[i] == '>' && a[i + 1] == '>')
			{
				if (tt->quote && first)
				{
					cmd->cmd = a;
				}
				else if (tt->quote && !first)
					ft_push(&cmd->args, ft_new_node(a));
				else
				{
					t_queue *yy = ft_pop(&queue);
					cmd->append = ((t_elem*)yy->data)->s;
				}
			}
		}
		else
		{
			if (first)
				cmd->cmd = tt->s;
			else
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
		printf ("in  = %s\n", aa->infile);
		printf ("append  = %s\n", aa->append);
		printf ("limiter  = %s\n", aa->limiter);
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
	return (queue_answer);
}

int	main()
{
	char	*a = "cmd|cmd|<< in cmd | cm'<'>> out";

	t_queue *q = ft_part_1(a);
	printf ("-------------------------------------------------\n\n");
	q = ft_part_2(q);
	printf ("-------------------------------------------------\n\n");
	
	q = ft_part_3(q);
	printf ("-------------------------------------------------\n\n");

	q = ft_part_4(q);
	printf ("-------------------------------------------------\n\n");
	q = ft_part_5(q);
	printf ("-------------------------------------------------\n\n");
	return 0;
}