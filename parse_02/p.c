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
	if (a[0] == '<' || a[0] == '>')
		return (1);
	return 0;
}
void	ft_token_err(t_queue *q, char *a)
{
	if (!q->next)
	{
		printf ("syntax error near unexpected token `newline'\n");
		exit(1);
	}
	if (a[0] == '>' && a[1] == '>' && a[2])
	{
		printf ("bash: syntax error near unexpected token `%s'\n", a+2);
	}
	if (a[0] == '<' && a[1] == '<' && a[2])
	{
		printf ("bash: syntax error near unexpected token `%s'\n", a+2);
	}
	if (a[0] == '<' && a[1] == '<' && a[2])
	{
		printf ("bash: syntax error near unexpected token `%s'\n", a+2);
	}
}

void	prin(t_queue *qq, char *s)
{
	t_queue *q = qq;
	while (q)
	{
		printf ("%s =     %s \n", s, q->data);
		q = q->next;
	}
}
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
			if (a[i] == '<' && a[i + 1] == '<')
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
					ft_push(&cmd->infile ,ft_new_node(((t_elem*)yy->data)->s));
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
					ft_push(&cmd->outfile ,ft_new_node(((t_elem*)yy->data)->s));
					cmd->relation = "trunc";
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
					ft_push(&cmd->outfile ,ft_new_node(((t_elem*)yy->data)->s));
					cmd->relation = "append";
				}
			}
		}
		else
		{
			if (first)
			{
				cmd->cmd = tt->s;
				first = 0;
			}
			else
				ft_push(&cmd->args, ft_new_node(a));
		}
		
	}
	ft_push(&queue_answer, ft_new_node(cmd));
		
	t_queue *q = queue_answer;
	while (q)
	{
		printf ("------------------------------66--------------------\n\n");
		t_cmd_wrapper *aa = q->data;
		printf ("cmd = %s\n", aa->cmd);
		prin(aa->outfile, "out");
		prin(aa->infile, "in ");
		prin(aa->append, "append");
		printf ("re    %s\n", aa->relation);
		printf( "limiter--> %s\n",aa->limiter);
		prin(aa->args, "arg");
		printf ("\n------------------------------66--------------------\n\n");
		q = q->next;
	}
	return (queue_answer);
}

int	ft_is_token2(char *a)
{
	if (*a == '|' || *a == '>' || *a == '<')
		return (1);
	return 0;
}

void	ft_check_cmds(t_queue *qq)
{
	t_queue	*q = qq;

	while (q)
	{
		t_elem	*tt = q->data;

		if (ft_is_token(tt->s))
		{
			if (strlen(tt->s) > 2)
			{
				printf ("syntax err ");
				exit (1);
			}
			else
			{
				if (!q->next || ft_is_token2(((t_elem*)q->next->data)->s))
				{
					printf ("syntax err ");
					exit (1);
				}
			}
		}
		q = q->next;
	}
}

int	main()
{
	char	*a = "<< cmd|cmd -l|<<  in cmd | cm'<'> out >>  out2 > out3      | ls '$USER' ";
	//char	*a = "echo '\"'hh$USER'\"'";
	// ls > out > out2 >> out3

	t_queue *q = ft_part_1(a);
	printf ("-------------------------------------------------\n\n");

	q = ft_part_2(q);
	printf ("-------------------------------------------------\n\n");
	
	q = ft_part_3(q);
	printf ("-------------------------------------------------\n\n");

	q = ft_part_4(q);
	printf ("-------------------------------------------------\n\n");

	ft_check_cmds(q);


	q = ft_part_5(q);
	printf ("-------------------------------------------------\n\n");

	return 0;
}
