/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlazrak <zlazrak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 19:27:22 by zlazrak           #+#    #+#             */
/*   Updated: 2023/02/18 15:31:54 by zlazrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "vector.h"


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
	node->content = content;
	node->next = NULL;
	return (node);
}


/******************/

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

void	ft_print(t_queue *q)
{
	while (q)
	{
		printf ("%s 	|", q->data);
		q = q->next;
	}
	printf ("\n");
}

t_queue	*ft_part_5(t_queue *q)
{
	t_queue	*queue_answer = NULL;
	t_queue	*temp;
	int 	i = 0;
	char	*a;
	int		f = 0;

	t_cmd_parse	*cmd = malloc (sizeof(t_cmd_parse));
	memset(cmd, 0, sizeof(*cmd));
	while (q)
	{
		temp = ft_pop(&q);
		t_elem	*tt = temp->data;
		a = tt->s;
		if ((a[0] == '>' || a[0] == '<' || a[0] == '|') && !tt->quote)
		{
			if(a[0] == '>')
			{
				if (a[1] == '>')
				{
					temp = ft_pop(&q);
					tt = temp->data;
					a = tt->s;
					ft_push(&cmd->outfile, ft_new_node(a));
					ft_push(&cmd->rel_1, ft_new_node("a"));
					continue;
				}
				else
				{
					temp = ft_pop(&q);
					tt = temp->data;
					a = tt->s;
					ft_push(&cmd->outfile, ft_new_node(a));
					ft_push(&cmd->rel_1, ft_new_node(strdup("trunc")));
					continue;
				}
			}
			if(a[0] == '<')
			{
				if (a[1] == '<')
				{
					temp = ft_pop(&q);
					tt = temp->data;
					a = tt->s;
					ft_push(&cmd->infile, ft_new_node(a));
					ft_push(&cmd->rel_2, ft_new_node("here_doc"));
					continue;
				}
				else
				{
					temp = ft_pop(&q);
					tt = temp->data;
					a = tt->s;
					ft_push(&cmd->infile, ft_new_node(a));
					ft_push(&cmd->rel_2, ft_new_node("input"));
					continue;
				}
			}
			if (a[0] == '|')
			{
				ft_push(&queue_answer, ft_new_node(cmd));
				cmd = malloc (sizeof(t_cmd_parse));
				memset(cmd, 0, sizeof(*cmd));
				f = 0;
			}


		}
		else
			ft_push(&cmd->cmd, ft_new_node(a));
	}
	ft_push(&queue_answer, ft_new_node(cmd));
	// t_queue *qq =queue_answer;

	// while (qq)
	// {
	// 	t_cmd_parse *c = qq->data;
	// 	printf ("cmd :   		");
	// 	ft_print(c->cmd);
	// 	printf ("infile :   	");
	// 	ft_print(c->infile);
	// 	printf ("rel in :   	");
	// 	ft_print(c->rel_2);
	// 	printf ("outfile :  	 ");
	// 	ft_print(c->outfile);
	// 	printf ("rel out :   	");
	// 	ft_print(c->rel_1);
	// 	qq = qq->next;
	// 	printf ("\n\n");
		
	// }
	return (queue_answer);
}

void	ft_join_dollar_env(t_vector *vec, t_vector *dollar, char **env);


char	*expand_dollar(char **env, char *a)
{
	t_vector	vec;
	t_vector	dollar;
	int i = -1;
;
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
				if (a[i] == '$')
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

/*
int	ft_print_err(t_queue *q, int tt)
{
	if (ft_isredirection(((t_elem*)q->data)->s) && !((t_elem*)q->data)->quote)
	{
		char *a= ((t_elem*)q->data)->s;
		if (strlen (a)>2)
		{
			if (strlen(a) == 3)
				printf ("zsh: parse error near `%c'\n", a[2]);//later bash
			else
			{
				if (a[2] == '>' && a[3] == '<')
					printf ("zsh: parse error near `>'\n");//later bash
				else
					printf ("zsh: parse error near `%c%c'\n", a[2], a[3]);//later bash

			}
			return -1;
		}
		else
		{
			if (strlen (a) == 2)
			{
				if (a[0] != a[1])
				{
					printf ("zsh: parse error near `%c'\n", a[1]);//later bash
					return (-1);
				}
			}
			else if (!q->next)
			{
				printf ("zsh: parse error near `newline'\n");//later bash
				return (-1);
			}
			else if (!tt)
			{
				return (ft_print_err(q->next, 1));
			}
		}
	}
	return (1);

}
*/

int	ft_is_token(char *a)
{
	return  (a[0] == '>' || a[0] == '<' || a[0] == '|');
}

int		part_3_5(t_queue *q)
{
	char	*a;
	char f = 0;
		while (q)
		{
			a = q->data;
			if (a[0] == '>' || a[0] == '<' || a[0] == '|')
			{
					if (a[0] == '|' && !f)
					{
						printf ("bash: syntax error near unexpected token `|'\n");
						return 1;
					}
					if (strlen(a) > 2)
					{
						if (a[2] == '>' && a[3] == '<')
						{
							printf ("bash: syntax error near unexpected token `>'\n");
							return 1;
						}
						if (strlen(a) == 3)
						{
							printf("bash: syntax error near unexpected token `%c'\n", a[2]);
							return 1;
						}
						else
							if (strlen(a) >= 3)
							{
								printf("bash: syntax error near unexpected token `%c%c'\n", a[2], a[3]);
								return 1;
							}	
					}
					else if (q->next && ft_is_token(q->next->data))
					{
						a = q->next->data;
						if (a[0] == '|')
						{
							printf ("bash: syntax error near unexpected token `|'\n");
							return 1;
						}
						/*if (strlen(a) > 2)
						{
							if (a[2] == '>' && a[3] == '<')
								printf ("bash: syntax error near unexpected token `>'\n");
							if (strlen(a) >= 3)
							{
								printf("bash: syntax error near unexpected token `%c%c'\n", a[0], a[1]);
							}
						}
						else
								printf("bash: syntax error near unexpected token `%c'\n", a[0]);
*/
					}
					else if (!q->next)
					{
						printf ("bash: syntax error near unexpected token `newline'\n");
						return 1;
					}
			}
			f = 1;
			q = q->next;
		}
		return 0;
}

int	check_enclosed_quotes(char	*a)
{
	int 	i;
	int		f;
	char	c;

	i = 0;
	f = 0;
	while (a[i])
	{
		if ((a[i] == '\'' || a[i] == '\"') && !f)
		{
			c = a[i];
			f = 1;
		}
		else if (f && a[i] == c)
			f = 0;
		i++;
	}
	return (f);
}

char	**ft_cp(t_queue *q)
{
	char	**answer = NULL;
	int	s = ft_q_size(q);
	if (!s) return NULL;
	answer = malloc (sizeof(char *) * (s + 1));
	int i = 0;
	while (q)
	{
	
		answer[i] = strdup(q->data);
		i++;
		q = q->next;
	}
	answer[i] = NULL;
	return answer;
}

void	ft_toexec(t_list	**cmd, t_queue *q)
{
	t_cmd_package	*c;

	while (q)
	{
		c = malloc (sizeof (t_cmd_package));
		memset(c, 0, sizeof(*c));
		c->cmd = ft_cp(((t_cmd_parse*)q->data)->cmd);
		c->outfile = ft_cp(((t_cmd_parse*)q->data)->outfile);
		c->infile = ft_cp(((t_cmd_parse*)q->data)->infile);
		c->rel_1 = ft_cp(((t_cmd_parse*)q->data)->rel_1);
		c->rel_2 = ft_cp(((t_cmd_parse*)q->data)->rel_2);
		ft_lstadd_back(cmd, ft_lstnew(c));
		q = q->next;
	}	
}

int	main(int c, char **aa, char **e)
{
	//char	*a = "cmd k|cmd -l|<<  in cmd | cm'<'> out >  out2 > out3      | ls \"'$USER'\" ";
	// char	*a = ">lol echo > test>lol>test>>lol>>testo mdr >lol test >test | cat test << ok < infile";
	// ls > out > out2 >> out3
	
	
	char *a = ""  ;
	t_queue *q = ft_part_1(a);
	printf ("-------------------------------------------------\n\n");

	q = ft_part_2(q);
	printf ("-------------------------------------------------\n\n");
	
	q = ft_part_3(q);
	printf ("-------------------------------------------------\n\n");

	if (part_3_5(q))
		exit(42);

	
	q = ft_part_4(q, e);
	printf ("-------------------------------------------------\n\n");
	q = ft_part_5(q);

	int s = ft_q_size(q);
	t_list	*cmd = NULL;

	ft_toexec(&cmd, q);
//	printf ("%s\n", cmd->content->cmd[1]);
	//printf ("---> %s \n", expand_dollar(e, a));
	t_list *ty = cmd;
		printf ("heeeeer\n");
	while (ty)
	{
		printf("cmd :				"); ft_p(ty->content->cmd);
	printf ("\n");

		printf("outfile :			"); ft_p(ty->content->outfile);
	printf ("\n");

		printf("rel_1:				"); ft_p(ty->content->rel_1);
	printf ("\n");

		printf("infile :			"); ft_p(ty->content->infile);
	printf ("\n");

		printf("rel_2 :			"); ft_p(ty->content->rel_2);
		printf ("\n\n");
		ty = ty->next;
	}
	
	return 0;
}

void	ft_p(char **a)
{
	int i = 0;
	if (!a)
		return;
	while (a[i])
	{
		printf ("%s   | ", a[i++]);
	}
	printf ("\n");
}