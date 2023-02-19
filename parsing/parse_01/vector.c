typedef struct s_vector
{
	char	*string;
	int		size;
	int		i;
} t_vector ;

void	ft_push_back(t_vector *vec, char data)
{
	char	*new;
	int		j;

	if (vec->i && vec->i == vec->size)
	{
		new = malloc(sizeof(char) * (vec->size * 2));
		j = 0;
		while (vec->string[j])
		{
			new[j] = vec->string[j];
			j++;
		}
		new[j++] = data;
		new[j] = '\0';
		free (vec->string);
		vec->string = new;
		vec->i = j;
		return ;
	}
	vec->string[vec->i++] = data;
	vec->string[vec->i] = '\0';
	// printf ("here\n");
}

void	ft_create_vector(t_vector *vec, int size)
{
	vec->size = size;
	vec->string = malloc(sizeof(char) * size);
	vec->i = 0;
}