/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeshing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samymone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 15:21:55 by samymone          #+#    #+#             */
/*   Updated: 2019/12/21 13:54:04 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
 * потом добавить чистку комнат и муравьев, тк если все збс при считывании, то
 * нужно будет все фришить в конце программы
 */

void		free_map(t_main *map)
{
	if (map)
	{
		free(map);
	}
}

void		free_rooms(t_room *room)
{
	if (!room)
		return ;
	while(room->next)
		free_rooms(room->next);
	if (room->name)
		free(room->name);
	free(room);
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
