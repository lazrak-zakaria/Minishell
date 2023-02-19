/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_part_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlazrak <zlazrak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 11:53:04 by zlazrak           #+#    #+#             */
/*   Updated: 2023/02/19 14:55:44 by zlazrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_join_dollar(t_vector **vec, t_vector *vec_dollar, t_yassir *ys);
int		ft_dollar_ok(char c);
char	*ft_expand_dollar(char *a, t_yassir *ys);
void	ft_norm_expand(char *a, t_vector *vec, t_yassir *ys, int *i);


static int	_abs(int n)
{
	if (n < 0)
		return (n * (-1));
	return (n);
}

static int	int_len(int n)
{
	int	l;

	l = 0;
	if (!n)
		return (1);
	while (n)
	{
		n /= 10;
		l++;
	}
	return (l);
}

char	*ft_itoa(int n)
{
	int		l;
	int		i;
	char	*a;

	l = int_len(n);
	if (n < 0)
		l++;
	a = (char *)malloc(sizeof(char) * (l + 1));
	if (!a)
		return (NULL);
	i = 0;
	if (n < 0)
		a[i++] = '-';
	a[l--] = '\0';
	while (l >= i)
	{
		a[l--] = _abs(n % 10) + '0';
		n /= 10;
	}
	return (a);
}


int	ft_find(char *a, char c)
{
	int i = 0;
	while (a[i] && a[i] != c)
		i++;
	return (a[i] != '\0');
}

void	ft_norm_part4(char *a, t_var *var)
{
	while (a[var->i])
	{
		if (a[var->i] == '\'' || a[var->i] == '\"')
		{
			var->c = a[var->i++];
			while (a[var->i] && a[var->i] != var->c)
				ft_push_back(&var->vec, a[var->i++]);
			if (!a[var->i])
				break ;
			++var->i;
		}
		else
			ft_push_back(&var->vec, a[var->i++]);
	}
}

t_queue	*ft_part_4(t_queue *queue, t_yassir *ys)
{
	t_var	var;
	t_elem	*element;
	char	*a;

	var.queue_answer = NULL;
	while (queue)
	{
		var.i = 0;
		var.flag = 0;
		ft_create_vector(&var.vec, 2);
		var.vec.string[0] = '\0';
		var.temp_queue = ft_pop(&queue);
		a = var.temp_queue->data;
		element = malloc (sizeof (t_elem));
		element->s = NULL;
		element->quote = (a[0] == '\'' || a[0] == '\"');
		if (ft_find(a, '$'))
		{
			element->s = ft_expand_dollar(a, ys);
			if (!element->s)
				element->s = var.vec.string;
			else
				free (var.vec.string);
			ft_push(&var.queue_answer, ft_new_node(element));
			continue ;
		}
		ft_norm_part4(a, &var);
		element->s = var.vec.string;
		ft_push(&var.queue_answer, ft_new_node(element));
	}
	return (var.queue_answer);
}

int	ft_dollar_ok(char c)
{
	int	f;

	f = ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
			|| (c >= '0' && c <= '9'));
	return (f);
}

char	*ft_expand_dollar(char *a, t_yassir *ys)
{
	t_vector	vec;
	int			i;

	memset(&vec, 0, sizeof(vec));
	i = 0;
	while (a[i])
	{
		if (a[i] == '\'')
		{
			i++;
			while (a[i] && a[i] != '\'')
				ft_push_back(&vec, a[i++]);
		}
		else if (a[i] == '\"')
		{
			i++;
			while (a[i] && a[i] != '\"')
				ft_norm_expand(a, &vec, ys, &i);
		}
		else
		{
			ft_norm_expand(a, &vec, ys, &i);
		}
	}
	return (vec.string);
}

void	ft_norm_expand(char *a, t_vector *vec, t_yassir *ys, int *i)
{
	t_vector	vec_dollar;
	int			flag;

	flag = 0;
	if (a[*i] == '$')
	{
		memset(&vec_dollar, 0, sizeof(vec_dollar));
		ft_push_back(&vec_dollar, a[(*i)++]);
		if (a[(*i)] == '?')
			ft_push_back(&vec_dollar, a[(*i)++]);
		while (ft_dollar_ok(a[(*i)]))
			ft_push_back(&vec_dollar, a[(*i)++]);
		flag = 1;
	}
	if (flag)
	{
		ft_join_dollar(&vec, &vec_dollar, ys);
	}
	else
		ft_push_back(vec, a[(*i)++]);
}

void	ft_join_dollar(t_vector **vec, t_vector *vec_dollar, t_yassir *ys)
{
	char	*a;
	int		i;
	int		j;

	if (vec_dollar->string[1] == '?')
	{
		a = ft_itoa(ys->exit_status);
		i = 0;
		while (a && a[i])
			ft_push_back(*vec, a[i++]);
		free (a);
	}
	else
	{
		if (vec_dollar->string[1])
			j = 1;
		ft_push_back(vec_dollar, '=');
		a = vec_dollar->string;
		if (j)
			a = vec_dollar->string + 1;
		j = strlen(a);
		i = 0;
		while (ys->env && ys->env[i])
		{
			if (!strncmp(a, ys->env[i], j))
			{
				while (ys->env[i][j])
					ft_push_back(*vec, ys->env[i][j++]);
				break ;
			}
			++i;
		}
	}
	free (vec_dollar->string);
}
