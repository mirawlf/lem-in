/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_useless_links.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samymone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 15:52:05 by samymone          #+#    #+#             */
/*   Updated: 2020/02/25 15:52:07 by samymone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <mach/vm_region.h>
#include "lemin.h"

void			dead_ends(t_main *map)
{
	t_room		*rooms;
	t_link		*links;

	rooms = map->all_rooms_here;
	links = map->all_links_here;
	while (links)
	{
		links->first_room->neighbours += 1;
		links->second_room->neighbours += 1;
		links = links->next;
	}
	while (rooms)
	{
		if (rooms->neighbours == 1 && rooms != map->start && rooms != map->end)
			rooms->is_dead_end = 1;
		rooms = rooms->next;
	}
}

static int		appoint_level(t_room *room, t_link *link, int lvl)
{
	room->level = lvl;
	link->checked = 1;
	return (1);
}

void			next_levels(t_main *map, int max_curr_lvl)
{
	t_link		*link;
	int			change;

	link = map->all_links_here;
	change = 0;
	while (link)
	{
		if (link->checked)
		{
			link = link->next;
			continue;
		}
		if (link->first_room->level == max_curr_lvl
			&& !link->second_room->level && !link->second_room->is_dead_end)
			change = appoint_level(link->second_room, link, max_curr_lvl + 1);
		else if (link->second_room->level == max_curr_lvl
				 && !link->first_room->level && !link->first_room->is_dead_end)
			change = appoint_level(link->first_room, link, max_curr_lvl + 1);
		link = link->next;
	}
	if (change == 1)
		next_levels(map, max_curr_lvl + 1);
}

void			count_inputs_and_outputs(t_main *map)
{
	t_link		*link;

	link = map->all_links_here;
	while (link)
	{
		if (link->first_room == map->end ||
			link->second_room->level < link->first_room->level)
		{
			link->first_room->inputs++;
			link->second_room->outputs++;
		}
		else if (link->second_room == map->end ||
				 link->first_room->level < link->second_room->level)
		{
			link->second_room->inputs++;
			link->first_room->outputs++;
		}
		link = link->next;
	}
}