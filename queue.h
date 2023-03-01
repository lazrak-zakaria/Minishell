/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlazrak <zlazrak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 12:59:04 by yel-mass          #+#    #+#             */
/*   Updated: 2023/03/01 13:20:04 by zlazrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_H
# define QUEUE_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>

typedef struct s_queue
{
	void			*data;
	struct s_queue	*next;
}	t_queue;

t_queue	*ft_new_node(void *data);
void	ft_push(t_queue **top, t_queue *q);
t_queue	*ft_pop(t_queue **top);
int		ft_q_size(t_queue *top);

#endif