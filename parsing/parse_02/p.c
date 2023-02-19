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

// int		ft_is_token(char *a)
// {
// 	if (a[0] == '<' || a[0] == '>')
// 		return (1);
// 	return 0;
// }
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

// void	prin(t_queue *qq, char *s)
// {
// 	t_queue *q = qq;
// 	while (q)
// 	{
// 		printf ("%s =     %s \n", s, q->data);
// 		q = q->next;
// 	}
// }
// t_queue	*ft_part_5(t_queue *queue)
// {
// 	t_queue		*queue_answer = NULL;
// 	t_queue		*temp;
// 	int			i;
// 	char		*a;
// 	int			first;
// 	t_vector	vec;
// 	char		c;
// 	t_cmd_wrapper	*cmd;

// 	first = 1;
// 		cmd = malloc(sizeof(*cmd));
// 		memset(cmd, 0, sizeof(*cmd));
// 	while (queue)
// 	{
// 		temp = ft_pop(&queue);
// 		t_elem	*tt = temp->data;
// 		char	*a = tt->s;
// 		i = 0;
// 		if (a[i] == '|' && !a[i + 1])
// 		{
// 			ft_push(&queue_answer, ft_new_node(cmd));
// 			cmd = malloc(sizeof(*cmd));
// 			memset(cmd, 0, sizeof(*cmd));
// 			first = 1;
// 			continue;
// 		}
// 		if (ft_is_token(a))
// 		{
// 				//	printf ("+++++++++++++++++++++++++++++++++++++\n");
// 			if (a[i] == '<' && a[i + 1] == '<')
// 			{
// 				if (tt->quote && first)
// 				{
// 					cmd->cmd = a;
// 				}
// 				else if (tt->quote && !first)
// 					ft_push(&cmd->args, ft_new_node(a));
// 				else
// 				{
// 					t_queue *yy = ft_pop(&queue);
// 					cmd->limiter = ((t_elem*)yy->data)->s;
// 				}
// 			}
// 			else if (a[i] == '<' && a[i + 1] == '\0')
// 			{
// 				if (tt->quote && first)
// 				{
// 					cmd->cmd = a;
// 				}
// 				else if (tt->quote && !first)
// 					ft_push(&cmd->args, ft_new_node(a));
// 				else
// 				{
// 					t_queue *yy = ft_pop(&queue);
// 					ft_push(&cmd->infile ,ft_new_node(((t_elem*)yy->data)->s));
// 				}
// 			}
// 			else if (a[i] == '>' && a[i + 1] == '\0')
// 			{
// 				if (tt->quote && first)
// 				{
// 					cmd->cmd = a;
// 				}
// 				else if (tt->quote && !first)
// 					ft_push(&cmd->args, ft_new_node(a));
// 				else
// 				{
// 					t_queue *yy = ft_pop(&queue);
// 					ft_push(&cmd->outfile ,ft_new_node(((t_elem*)yy->data)->s));
// 					cmd->relation = "trunc";
// 				}
// 			}
// 			else if (a[i] == '>' && a[i + 1] == '>')
// 			{
// 				if (tt->quote && first)
// 				{
// 					cmd->cmd = a;
// 				}
// 				else if (tt->quote && !first)
// 					ft_push(&cmd->args, ft_new_node(a));
// 				else
// 				{
// 					t_queue *yy = ft_pop(&queue);
// 					ft_push(&cmd->outfile ,ft_new_node(((t_elem*)yy->data)->s));
// 					cmd->relation = "append";
// 				}
// 			}
// 		}
// 		else
// 		{
// 			if (first)
// 			{
// 				cmd->cmd = tt->s;
// 				first = 0;
// 			}
// 			else
// 				ft_push(&cmd->args, ft_new_node(a));
// 		}
		
// 	}
// 	ft_push(&queue_answer, ft_new_node(cmd));
		
// 	t_queue *q = queue_answer;
// 	while (q)
// 	{
// 		printf ("------------------------------66--------------------\n\n");
// 		t_cmd_wrapper *aa = q->data;
// 		printf ("cmd = %s\n", aa->cmd);
// 		prin(aa->outfile, "out");
// 		prin(aa->infile, "in ");
// 		prin(aa->append, "append");
// 		printf ("re    %s\n", aa->relation);
// 		printf( "limiter--> %s\n",aa->limiter);
// 		prin(aa->args, "arg");
// 		printf ("\n------------------------------66--------------------\n\n");
// 		q = q->next;
// 	}
// 	return (queue_answer);
// }

// int	ft_is_token2(char *a)
// {
// 	if (*a == '|' || *a == '>' || *a == '<')
// 	{
// 			return (1);
// 	}
// 	return 0;
// }
// void	print_err(char	*a);

// void	ft_check_cmds(t_queue *qq)
// {
// 	t_queue	*q = qq;

// 	while (q)
// 	{
// 		t_elem	*tt = q->data;

// 		if (ft_is_token(tt->s))
// 		{
// 			if (strlen(tt->s) > 2)
// 			{
// 				printf ("syntax err \n		");print_err(tt->s + 2);
				
// 				exit (1);
// 			}
// 			else
// 			{
// 				if (!q->next)
// 				{
// 					printf ("near newline \n");
// 					exit (1);
// 				}
// 				else if (ft_is_token2(((t_elem*)q->next->data)->s) && !((t_elem*)q->next->data)->quote)
// 				{
// 					printf ("syntax err \n		");print_err(((t_elem*)q->next->data)->s);
// 					exit (1);
// 				}
// 			}
// 		}
// 		q = q->next;
// 	}
// }

// void	print_err(char	*a)
// {
// 	if (a[0] == '<' && a[1] == '>')
// 	{
// 		printf("bash: syntax error near unexpected token `<>'\n");
// 	}
// 	else if (a[0] == '>' && a[1] == '>')
// 		printf("bash: syntax error near unexpected token `>>'\n");
// 	else if (a[0] == '<' && a[1] == '<')
// 		printf("bash: syntax error near unexpected token `<<'\n");
// 	else 
// 		printf("bash: syntax error near unexpected token `%c'\n", a[0]);
// }

void	ft_join_dollar_env(t_vector *vec, t_vector *dollar, char **env);


char	*expand_dollar(char **env, char *a)
{
	t_vector	vec;
	t_vector	dollar;
	int i = -1;
	while (a[++i])
	{
		if (a[i] == '$')
			break;
	}
	if (!a[i])
		return (a);
	i = 0;
	int f = 0;
	ft_create_vector(&vec, 50);
	while (a[i])
	{
		if (a[i] == '\'')
		{
			i++;
			while (a[i] && a[i] != '\'')
			{
				ft_push_back(&vec, a[i++]);
			}
		}
		else if (a[i] == '\"')
		{
			i++;
			while (a[i] && a[i] != '\"')
			{
				if (a[i] =='$')
				{
					ft_create_vector(&dollar, 50);
					i++;
					while (a[i] && (a[i] != '\'' && a[i] != '"'))
						ft_push_back(&dollar, a[i++]);
					f = 1;
				}
				if (f)
				{
					ft_join_dollar_env(&vec, &dollar, env);
					f = 0;
					//i++;
					continue;
				}
				ft_push_back(&vec, a[i++]);
			}
		}
		else
		{
			if (a[i] == '$')
				{
					ft_create_vector(&dollar, 50);
					i++;
					while (a[i] && (a[i] != '\'' && a[i] != '"' && a[i] != ' '
						&& a[i] != '%') )
						ft_push_back(&dollar, a[i++]);
					f = 1;
				}
				if (f)
				{
					ft_join_dollar_env(&vec, &dollar, env);
					f = 0;
					//i++;
					continue;
				}
			ft_push_back(&vec, a[i]);
		}
		i++;
	}
	return vec.string;
}

void	ft_join_dollar_env(t_vector *vec, t_vector *dollar, char **env)
{
	int i = 0;
	ft_push_back(dollar, '=');
	printf ("^^^^  %s\n", dollar->string);
	while (env[i])
	{
		if (!strncmp(dollar->string , env[i], strlen(dollar->string)))
		{
			int j = strlen(dollar->string);
			char *a = env[i];
			while (a[j])
				ft_push_back(vec, a[j++]);
			return;
		}
		i++;
	}
}

int	main(int c, char **aa, char **e)
{
	//char	*a = "<< cmd|cmd -l|<<  in cmd | cm'<'> out >>  out2 > out3      | ls '$USER' ";
	char	*a = "echo  hh\"aaa\"";
	// ls > out > out2 >> out3

	t_queue *q = ft_part_1(a);
	printf ("-------------------------------------------------\n\n");

	q = ft_part_2(q);
	printf ("-------------------------------------------------\n\n");
	
	q = ft_part_3(q);
	printf ("-------------------------------------------------\n\n");

	q = ft_part_4(q);
	printf ("-------------------------------------------------\n\n");

	printf ("---> %s \n", expand_dollar(e, "hh'$USER%  |'"));
	return 0;
}
