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

#include <mach/vm_region.h>
#include "lemin.h"

void		delete_useless_links(t_main *map)
{
	t_link	*link;
	t_link	*tmp;

	link = map->all_links_here;
	if (map->all_links_here->first_room->is_dead_end || map->all_links_here->second_room->is_dead_end ||
	map->all_links_here->first_room->level == map->all_links_here->second_room->level)
	{
		tmp = map->all_links_here;
		map->all_links_here = map->all_links_here->next;
		free(tmp);
	}
	else
	{
		tmp = map->all_links_here;
		link = tmp->next;
		while (link)
		{
			if(link->first_room->is_dead_end || link->second_room->is_dead_end ||
			   link->first_room->level == link->second_room->level)
			{
				link->first_room->is_dead_end ? link->second_room->neighbours-- : link->first_room->neighbours--;
				tmp->next = link->next;
				link = NULL;
				free(link);
			}
			if (tmp->next)
			{
				tmp = tmp->next;
				link = tmp->next;
			}
		}
	}
}

void 		delete_other_input_rooms(t_room *current, t_room *second, t_main *map)
{
	t_link	*link;
	t_link	*tmp;

	if ((map->all_links_here->first_room == current && map->all_links_here->second_room != second) ||
	(map->all_links_here->second_room == current && map->all_links_here->first_room != second))
	{
		tmp = map->all_links_here;
		map->all_links_here = map->all_links_here->next;
		free(tmp);
	}
	else
	{
		tmp = map->all_links_here;
		link = tmp->next;
		while (link)
		{
			if (link->first_room == current && link->second_room != second)
			{
				current->inputs--;
				second->outputs--;
				tmp->next = link->next;
				link = NULL;
				free(link);
			}
			else if (link->second_room == current && link->first_room != second)
			{
				second->inputs--;
				current->outputs--;
				tmp->next = link->next;
				link = NULL;
				free(link);
			}
			if (tmp->next)
			{
				tmp = tmp->next;
				link = tmp->next;
			}
		}
	}
}

void 		exclude_forks(t_main * map)
{
	t_room	*room;
	t_link	*link;
	int 	change;

	room = map->all_rooms_here;
	change = 0;
	while (room)
	{
		if (room->level == 2)
		{
			if (room->outputs == 1)
			{
				link = map->all_links_here;
				while(link)
				{
					if (link->first_room == room && link->second_room != map->start
						&& link->second_room != map->end && link->second_room->inputs > 1)
					{
						delete_other_input_rooms(link->second_room, link->first_room, map);
						change = 1;
					}
					else if (link->second_room == room && link->first_room != map->start
					&& link->first_room != map->end && link->first_room->inputs > 1)
					{
						delete_other_input_rooms(link->first_room, link->second_room, map);
						change = 1;
					}
					link = link->next;
				}
			}
		}
		room = room->next;
	}
	if (change == 1)
		exclude_forks(map);
}

void		count_inputs_and_outputs(t_main *map)
{
	t_link	*link;

	link = map->all_links_here;
	while(link)
	{
		if (link->first_room == map->end)
		{
			link->first_room->inputs++;
			link->second_room->outputs++;
		}
		else if (link->second_room == map->end)
		{
			link->second_room->inputs++;
			link->first_room->outputs++;
		}
		else if (link->first_room->level < link->second_room->level)
		{
			link->first_room->outputs++;
			link->second_room->inputs++;
		}
		else
		{
			link->second_room->outputs++;
			link->first_room->inputs++;
		}
		link = link->next;
	}
	exclude_forks(map);
}

