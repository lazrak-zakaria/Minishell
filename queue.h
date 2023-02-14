#ifndef QUEUE_H
# define QUEUE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef void* TYPE;

typedef struct s_queue
{
    void*            data;
    struct s_queue *next;
} t_queue;

t_queue	*ft_new_node(TYPE data);
void    ft_push(t_queue **top, t_queue *q);
t_queue  *ft_pop(t_queue **top);
int		ft_q_size(t_queue *top);
#endif