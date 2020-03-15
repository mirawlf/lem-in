/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_searching.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samymone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 19:20:54 by samymone          #+#    #+#             */
/*   Updated: 2020/03/15 19:21:00 by samymone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		second_searching(t_main *map)
{
	t_room	*room;

	room = map->all_rooms_here;
	while (room)
	{
		if (room->where == map->end && !room->from)
			search_previous_room(room, map);
		room = room->next;
	}
}
