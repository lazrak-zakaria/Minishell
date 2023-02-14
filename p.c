#include "minishell.h"
#include "queue.h"

char	*ft_substr(char	*a, int s, int e);

char	**get_cmd(char *a)
{
	t_queue	*queue = NULL;
	int		i;
	int		f;
	char	g;
// char *a = "cat 'main.c' '[[' | wc -l | ls  > 'la'";
	i = 0;
	while (a[i])
	{
		int j = 0;
		if (a[i] != ' ' && a[i])
		{
			if (a[i] == '\"')
				g = '"';
			else if (a[i] == '\'')
				g = '\'';
			else
				g = ' ';
			j = i;
			if (a[i] == '\'' || a[i] == '"')
				j = i + 1;
			while (a[j] && a[j] != g)
				j++;
			if (i == j) continue;
			ft_push(&queue, ft_new_node(ft_substr(a, i, j)));
			if (!a[j])
				break;
			i = j + 1;
			continue;
		}
		i++;
	}
	int size = ft_q_size(queue);
	char	**answer = NULL;
	answer = malloc (sizeof(char*) * (size + 1));
	i = 0;
	while (i < size)
	{
		t_queue *tmp;
		tmp = ft_pop(&queue);
		answer[i++] = tmp->data;
		free (tmp);
	}
	answer[i] = 0;
	return (answer);
}

char	*ft_substr(char	*a, int s, int e)
{
	char	*answer;
	int		k;
	answer = malloc (sizeof (char) * (e - s + 1 + 1));
	k = 0;
	while (s <= e && a[s])
		answer[k++] = a[s++];
	answer[k] = '\0';
	//printf ("%s\n", answer);
	return (answer);
}

char	*ft_handle(char *a)
{
	return NULL;
}

// t_queue	*ft_to_cmd(char **a)   // what if '<' first ?)
// {
// 	t_queue	*queue = NULL;
// 	t_cmd_wrapper	*cmd;
// 	int		i = 0;
// 	int 	c = 0;
// 	while (a[i])
// 	{
// 		if (c == 0)
// 		{
// 			cmd = malloc(sizeof(t_cmd_wrapper));
// 			cmd->outfile = "NULL";
// 			cmd->cmd = a[i];
// 			c = 1;
// 		}
// 		else
// 		{
// 			if (a[i][0] == '|' && a[i][1])    //    {
// 			{
// 				ft_push(&queue, ft_new_node(cmd));
// 				cmd = malloc(sizeof(t_cmd_wrapper));
// 				cmd->outfile = "NULL";
// 				cmd->cmd = &a[i][1];								//rp
// 				//printf ("%s_____\n", a[i]);
// 			}
// 			else if (a[i][0] == '|')
// 			{
// 				ft_push(&queue, ft_new_node(cmd));  //     }
// 				c = 0;
// 			}
// 			else if (a[i][0] == '<' && a[i][1])
// 			 	cmd->infile = &a[i][1];
// 			else if (a[i][0] == '<' && a[i][0] == ' ')
// 			 	cmd->infile = a[++i];
// 			else if (a[i][0] == '>' && a[i][1])
// 			 	cmd->outfile = &a[i][1];
// 			else if (a[i][0] == '>')
// 			 	cmd->outfile = a[++i];
// 			else
// 				cmd->args = &a[i];
// 		}
// 		i++;
// 	}
// 	ft_push(&queue, ft_new_node(cmd));
// 	while (queue)
// 	{
// 		printf ("%s\n", ((t_cmd_wrapper*)(queue->data))->cmd);
// 		printf ("%s\n", ((t_cmd_wrapper*)(queue->data))->outfile);
// 		ft_pop(&queue);
// 	}
// 	return (queue);
// }

int main()
{
	//char *a = "cat 'main.c' '[[' | wc-l | ls>'la'";
	// char *a = "cat\"main.c\" '|' wc|ls>'la'|ls|wc";
	// int i = 0;
	
	// char **aa = get_cmd(a);
	//  while (aa[i])
	// 	 printf ("%s\n", aa[i++]);
	//t_queue *t = ft_to_cmd(aa);
	// printf ("%d\n", ft_q_size(t));

	return (0);
}