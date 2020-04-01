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
		else if (link->second_room->level == link->first_room->level)
        {
		    link->second_room->equals += 1;
		    link->first_room->equals += 1;
        }
		link = link->next;
	}
}
