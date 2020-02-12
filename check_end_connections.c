/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_end_connections.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samymone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 14:46:43 by samymone          #+#    #+#             */
/*   Updated: 2020/02/12 14:46:46 by samymone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int 		decrease_end_connections(t_room *room, t_room *start, t_room *end)
{
	int 	i;
	t_room	*tmp;

	i = 0;
	while (tmp)
	{
		if (tmp != tmp->has_pair == 1 && tmp != start && tmp != end)
			i++;
		tmp = tmp->next;
	}
	return (i / 2);
}

void		check_end_connections(t_main *map)
{
	t_link	*link;
	t_room	*room;

	room = map->all_rooms_here;
	link = map->all_links_here;
	while (room)
	{
		link = map->all_links_here;
		while (link)
		{
			if (!link->has_pair && (link->first_room == room || link->second_room == room))
				{
					link->first_room->has_pair += 1;
					link->second_room->has_pair += 1;
					link->has_pair = 1;
				}
			link = link->next;
		}
		room = room->next;
	}
	map->end_connections = (map->end_connections > map->start_connections ? map->start_connections :
			map->end_connections - decrease_end_connections(map->all_rooms_here, map->start, map->end));
}

