/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlazrak <zlazrak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 10:38:04 by zlazrak           #+#    #+#             */
/*   Updated: 2023/02/12 11:02:29 by zlazrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int main(int ac, char **av, char **env)
{
	char	*p;

	if (ac != 1)
		return (0);
	p = NULL;
	while (1)
	{
		p = readline("--->");
		if (!p)
			return (1);
		add_history(p);
		parse(p);
	}
}