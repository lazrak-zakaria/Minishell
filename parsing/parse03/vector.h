#ifndef t
#define t
#include <stdlib.h>

typedef struct s_vector
{
	char	*string;
	int		size;
	int		i;
} t_vector ;

void	ft_push_back(t_vector *vec, char data);
void	ft_create_vector(t_vector *vec, int size);
#endif
