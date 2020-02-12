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

static	void	aux_for_levels(t_link *link, t_room *first, t_room *second,
		t_main *map)
{
	if (second != map->end)
	{
		second->level = first->level + 1;
		link->checked = 1;
	}
	else
		map->reached_end += 1;
}

static void		next_levels(t_main *map)
{
	t_link	*link;

	link = map->all_links_here;
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
				(!link->second_room->level || link->second_room->level == -10) && !link->checked)
			aux_for_levels(link, link->first_room, link->second_room, map);
		else if (link->second_room->level == map->max_current_level &&
				(!link->first_room->level || link->first_room->level == -10) && !link->checked)
			aux_for_levels(link, link->second_room, link->first_room, map);
		link = link->next;
	}
	if (map->reached_end < map->end_connections)
	{
		if (map->max_current_level == map->rooms)
			return;
		printf("%d  ", map->max_current_level);
		map->max_current_level += 1;
		next_levels(map);
	}
	}

void			*determine_levels(t_main *map)
{
	t_room	*tmp_room;
	t_link	*tmp_link;

	tmp_room = map->start;
	tmp_room->level = 1;
	tmp_link = map->all_links_here;
	while (tmp_link)
	{
		if (tmp_link->first_room == map->start)
		{
			tmp_link->second_room->level = 2;
			tmp_link->checked = 1;
		}
		else if (tmp_link->second_room == map->start)
		{
			tmp_link->first_room->level = 2;
			tmp_link->checked = 1;
		}
		tmp_link = tmp_link->next;
	}
	map->max_current_level = 2;
	map->end_connections = (map->end_connections > map->start_connections ? map->start_connections :
							map->end_connections - map->end_connections/map->start_connections);
	next_levels(map);
	map->end->level = -1;
}
