#include "../minishell.h"

void	ft_part_norm5(t_elem *e, t_cmd_parse *cmd, t_queue **queue, t_var *var);

void	ft_handle_out(char *a, t_cmd_parse *cmd, t_queue **queue, t_var *var)
{
	t_elem	*elem;
	char	*b;

	var->temp_queue = ft_pop(queue);
	elem = var->temp_queue->data;
	b = elem->s;
	ft_push(&cmd->file, ft_new_node(b));
	if (elem->dollar && !elem->quote && !b[0])
		ft_push(&cmd->rel, ft_new_node(strdup("BIGOUS")));
	else if (a[1])
		ft_push(&cmd->rel, ft_new_node(strdup("APPEND")));
	else
		ft_push(&cmd->rel, ft_new_node(strdup("TRUNC")));

}

void	ft_handle_in(char *a, t_cmd_parse *cmd, t_queue **queue, t_var *var)
{
	t_elem	*elem;
	char	*b;

	var->temp_queue = ft_pop(queue);
	elem = var->temp_queue->data;
	b = elem->s;
	ft_push(&cmd->file, ft_new_node(b));
	if (a[1])
		ft_push(&cmd->rel, ft_new_node(strdup("HERE_DOC")));
	else
		ft_push(&cmd->rel, ft_new_node(strdup("INPUT")));

}

t_queue	*ft_part_5(t_queue *queue)
{
	t_cmd_parse	*cmd;
	t_elem		*elem;
	t_var		var;
	char		*a;

	cmd = malloc(sizeof(t_cmd_parse));
	memset(cmd, 0, sizeof(*cmd));
	var.queue_answer = NULL;
	var.flag = 0;
	while (queue)
	{
		var.temp_queue = ft_pop(&queue);
		elem = var.temp_queue->data;
		if (var.flag)
		{
			cmd = malloc(sizeof(t_cmd_parse));
			memset(cmd, 0, sizeof(*cmd));
			var.flag = 0;
		}
		ft_part_norm5(elem, cmd, &queue, &var);
	}
	ft_push(&var.queue_answer, ft_new_node(cmd));
	return (var.queue_answer);
}

void	ft_part_norm5(t_elem *e, t_cmd_parse *cmd, t_queue **queue, t_var *var)
{
	char	*a;

	a = e->s;
	if ((a[0] == '>' || a[0] == '<' || a[0] == '|') && !e->quote)
	{
		if (a[0] == '>')
			ft_handle_out(a, cmd, queue, var);
		else if (a[0] == '<')
			ft_handle_in(a, cmd, queue, var);
		else
		{
			ft_push(&var->queue_answer, ft_new_node(cmd));
			var->flag = 1;
		}
	}
	else
	{
		ft_push(&cmd->cmd, ft_new_node(a));
	}
}

