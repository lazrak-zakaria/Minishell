#include "minishell.h"


int main()
{
	t_vector vec;
	ft_create_vector(&vec, 1);
	int i = 104;
while (i--)
{
	ft_push_back(&vec, 'a');
	printf ("here\n");
}
}
	