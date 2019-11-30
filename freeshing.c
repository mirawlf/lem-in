/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeshing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samymone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 15:21:55 by samymone          #+#    #+#             */
/*   Updated: 2019/11/30 15:21:56 by samymone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
 * потом добавить чистку комнат и муравьев, тк если все збс при считывании, то
 * нужно будет все фришить в конце программы
 */

void		free_map(t_map *map)
{
	if (map != NULL)
	{
		free(map);
	}
}

void		free_ant(int i, t_ant *ant)
{
	t_ant	*curr;

	while (i-- > 0)
	{
		if (ant->next)
			curr = ant->next;
		ant->num = 0;
		free(ant->prev);
		free(ant->next);
		free(ant->curr_room);
		ant = curr;
	}
	free(ant);
}
