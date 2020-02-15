/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samymone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 14:55:46 by samymone          #+#    #+#             */
/*   Updated: 2020/02/09 17:14:14 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static	int	aux_for_levels(t_link *link, t_room *first, t_room *second,
		t_main *map, int checked_rooms)
{
	if (second != map->end)
	{
		second->level = first->level + 1;
		link->checked = 1;
		return (1);
	}
	else
		map->reached_end += 1;
	return (0);
}

static void		next_levels(t_main *map, int checked_rooms) {
	t_link 		*link;
	int 		change;
	
	link = map->all_links_here;
	change = 0;
	while (link)
	{
		if (link->checked)
		{
			link = link->next;
			continue;
		}
//		if ((link->first_room == map->end && link->second_room->was_checked != map->iterations)
//		|| (link->second_room == map->end && link->first_room->was_checked != map->iterations))
//			map->end_connections--;
		if (link->first_room->level == map->max_current_level &&
			!link->second_room->level && !link->checked)
		{
			checked_rooms += aux_for_levels(link, link->first_room, link->second_room, map, checked_rooms);
			change = 1;
		}
		else if (link->second_room->level == map->max_current_level &&
				 !link->first_room->level && !link->checked)
		{
			checked_rooms += aux_for_levels(link, link->second_room, link->first_room, map, checked_rooms);
			change = 1;
		}
		else if (link->first_room->level && link->second_room->level && !link->checked)
			link->checked = 1;
		link = link->next;
	}
	if (change == 0)
		return;
	if (checked_rooms < map->rooms)
	{
		map->max_current_level += 1;
		next_levels(map, checked_rooms);
	}
	printf("rooms %d  map %d\n", checked_rooms, map->rooms);
}

void			*determine_levels(t_main *map)
{
	t_room	*tmp_room;
	t_link	*tmp_link;
	int 	checked_rooms;
	
	tmp_room = map->start;
	tmp_room->level = 1;
	tmp_link = map->all_links_here;
	checked_rooms = 1;
	while (tmp_link)
	{
		if (tmp_link->first_room == map->start)
		{
			tmp_link->second_room->level = 2;
			tmp_link->checked = 1;
			checked_rooms += 1;
		}
		else if (tmp_link->second_room == map->start)
		{
			tmp_link->first_room->level = 2;
			tmp_link->checked = 1;
			checked_rooms += 1;
		}
		tmp_link = tmp_link->next;
	}
	map->max_current_level = 2;
	next_levels(map, checked_rooms);
	map->end->level = -1;
}
