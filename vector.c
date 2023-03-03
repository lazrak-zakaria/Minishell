/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mass <yel-mass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 14:01:36 by zlazrak           #+#    #+#             */
/*   Updated: 2023/03/03 10:46:30 by yel-mass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

void	ft_push_back(t_vector *vec, char data)
{
	char	*new;
	int		j;

	if (vec->i + 1 >= vec->size)
	{
		if (!vec->size)
			vec->size = 2;
		new = malloc(sizeof(char) * (vec->size * 2));
		vec->size *= 2;
		j = 0;
		while (vec->string && vec->string[j])
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
}

void	ft_create_vector(t_vector *vec, int size)
{
	if (size < 0)
		size = 1;
	vec->size = size;
	vec->string = malloc(sizeof(char) * size);
	vec->i = 0;
}
