void	*ft_memset(void *a, int c, int size)
{
	char	*s;
	int		i;

	s = a;
	i = 0;
	while (i < size)
		s[i++] = c;
	return (a);
}
