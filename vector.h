/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mass <yel-mass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 12:58:24 by yel-mass          #+#    #+#             */
/*   Updated: 2023/02/27 12:58:56 by yel-mass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <stdlib.h>

typedef struct s_vector
{
	char	*string;
	int		size;
	int		i;
}	t_vector;

void	ft_push_back(t_vector *vec, char data);
void	ft_create_vector(t_vector *vec, int size);
#endif
