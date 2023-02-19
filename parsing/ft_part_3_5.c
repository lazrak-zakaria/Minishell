#include "../minishell.h"

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


void	ft_putstr_endll(char *a, int fd)
{
	write (fd, a, strlen(a));
//	write (fd, "\n", 1);
}

void ft_putchar_fd(char c, int fd)
{
	write (fd, &c, 1);
}

int	ft_is_token(char *a)
{
	return  (a[0] == '>' || a[0] == '<' || a[0] == '|');
}


int	ft_part_3_5(t_queue *q)
{
	char	*a;
	char	f;

	f = 0;
	while (q)
	{
		a = q->data;
		if (a[0] == '>' || a[0] == '<' || a[0] == '|')
		{
			if (a[0] == '|' && !f)
			{
				ft_putstr_endll("bash: syntax error near unexpected token `|'", 2);
				ft_putchar_fd('\n', 2);

				return 1;
			}
			if (strlen(a) > 2)
			{
				if (a[2] == '>' && a[3] == '<')
				{
					ft_putstr_endll("bash: syntax error near unexpected token `>'",2);
					ft_putchar_fd('\n', 2);
					return 1;
				}
				if (strlen(a) == 3)
				{
					ft_putstr_endll("bash: syntax error near unexpected token `", 2);
					ft_putchar_fd(a[2],	2);
					ft_putchar_fd('\'', 2);
					ft_putchar_fd('\n', 2);
					return 1;
				}
				else if (strlen(a) >= 3)
				{
					ft_putstr_endll("bash: syntax error near unexpected token `", 2);
					ft_putchar_fd(a[2],	2);
					ft_putchar_fd(a[3],	2);
					ft_putchar_fd('\'', 2);
					ft_putchar_fd('\n', 2);
					return 1;
				}	
			}
			else if (q->next && ft_is_token(q->next->data))
			{
				char	*b = a;
				a = q->next->data;
				if (a[0] == '|')
				{
					ft_putstr_endll("bash: syntax error near unexpected token `|'",2);
					ft_putchar_fd('\n', 2);
					return 1;
				}
				else if (b[0] == '|')
					return 0;
				if (strlen(a) >= 2)
				{
					if (a[0] == '>' && a[1] == '<')
						printf ("bash: syntax error near unexpected token `>'\n");
					if (strlen(a) >= 2)
					{
						printf("bash: syntax error near unexpected token `%c%c'\n", a[0], a[1]);
					}
				}
					else
						printf("bash: syntax error near unexpected token `%c'\n", a[0]);
			}
			else if (!q->next)
			{
				ft_putstr_endll("bash: syntax error near unexpected token `newline'",2);
				ft_putchar_fd('\n', 2);
				return 1;
			}
		}
		f = 1;
		q = q->next;
	}
	return (0);
}
