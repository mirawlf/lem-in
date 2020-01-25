/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samymone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 15:09:34 by samymone          #+#    #+#             */
/*   Updated: 2020/01/06 15:09:36 by samymone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include <stdio.h>

void		*search_necessary_rooms(t_main *map)
{
	t_room	*tmp;
	int 	i;
	int 	n;
	t_path	*path;

	tmp = map->start;
	i = -1;
	while (tmp->level != -1)
		tmp = tmp->next;
	search_previous_room(tmp, map);
	if (!(path = (t_path*)malloc(sizeof(t_path) * i)))
		return (NULL);
}


void		*search_previous_room(t_room *current, t_main *map)
{
	t_link	*link;

	link = map->all_links_here;
	while (link)
	{
		if (link->first_room == current && (link->first_room->level >= link->second_room->level || link->first_room->level == -1) && link->checked == 0)
		{
			link->first_room->is_part_of_path += 1;
			link->checked = 1;
			if (link->second_room->level != 1)
			{
				if (link->first_room != map->end)
				{
					if (link->first_room->from == NULL)
					{
						link->second_room->where = link->first_room;
						link->first_room->from = link->second_room;
					}
				}
				else
					link->second_room->where = link->first_room;
				search_previous_room(link->second_room, map);
			}
			else
				link->first_room->from = link->second_room;
		}
		else if (link->second_room == current && (link->second_room->level >= link->first_room->level || link->second_room->level == -1) && link->checked == 0)
		{
			link->second_room->is_part_of_path += 1;
			link->checked = 1;
			if (link->first_room->level != 1)
			{
				if (link->second_room != map->end)
				{
					if (link->second_room->from == NULL)
					{
						link->first_room->where = link->second_room;
						link->second_room->from = link->first_room;
					}
				}
				else
					link->first_room->where = link->second_room;
				search_previous_room(link->first_room, map);
			}
			else
				link->second_room->from = link->first_room;
		}
		link = link->next;
	}
}
