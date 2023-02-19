#include "minishell.h"


void ft()
{
	char *a ;
	int i = 9;
	while (i--)
	{
		a = readline("--->");
		add_history(a);
		free(a);
	}
}

int main()
{
	ft();
}