#include "minishell.h"

void	ft_print_queue(t_queue *q)
{
	while (q)
	{
		printf ("%s  ", q->data);
		q = q->next;
	}
	printf ("\n");
}

void	ft_print_ele(t_queue *q)
{
	t_elem *tr ;
	while (q)
	{
		tr = q->data;
		char *a = tr->s;

		printf ("%s  \n", a);
		q = q->next;
	}
}

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

int	main(int ac, char **av, char **env)
{
	t_queue	*q = NULL;
	t_yassir 	ys;

	memset(&ys, 0, sizeof(t_yassir));
	ys.env = env;
	//char *a = "\"'cmd -l'\" '|' \"'$USER'\" cm<d < ok >> inf|ile << her>edoc > outfile | cm|d3";
	char	*a= "''cmd -l | << ''h echo \"ok\" | cmd2 -a >> ap > out|cmd3|cmd4$USER!";
	q = ft_part_1(a);
	ft_print_queue(q);
	printf ("----------------------------------------------------------\n\n");

	q = ft_part_2(q);
	ft_print_queue(q);
	printf ("----------------------------------------------------------\n\n");

	q = ft_part_3(q);
	ft_print_queue(q);
	printf ("----------------------------------------------------------\n\n");

	ft_part_3_5(q);
	printf ("----------------------------------------------------------\n\n");
	
	q = ft_part_4(q, &ys);
	ft_print_ele(q);
	printf ("----------------------------------------------------------\n\n");

	q = ft_part_5(q);
	t_queue *ww = q;
	while (ww)
	{
		t_cmd_parse	*e = ww->data;
		printf ("cmd 		:  ");
		ft_print_queue(e->cmd);
		printf ("outfile 	:  ");
		ft_print_queue(e->outfile);
		printf ("rel_1 		:  ");
		ft_print_queue(e->rel_1);
		printf ("infile		:  ");
		ft_print_queue(e->infile);
		printf ("rel_2 		:  ");
		ft_print_queue(e->rel_2);
		printf ("\n\n");
		ww = ww->next;
	}
	printf ("----------------------------------------------------------\n\n");


}
