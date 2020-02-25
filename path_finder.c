/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samymone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 14:12:25 by samymone          #+#    #+#             */
/*   Updated: 2020/02/25 14:12:27 by samymone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void		second_rooms(t_room *room, t_main *map)
{
	t_path	*tmp;
	
	if (!map->paths)
	{
		if (!(map->paths = (t_path *)ft_memalloc(sizeof(t_path))))
			ft_error("malloc failed\n");
		map->paths->current = room;
	}
	else
	{
		tmp = map->paths;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = (t_path *)ft_memalloc(sizeof(t_path));
		tmp = tmp->next;
		tmp->current = room;
	}
}

static void	path_is_found(t_room *room, t_main *map)
{
	while (room->from != map->start)
		room = room->from;
	second_rooms(room, map);
}

void		milky_way(t_main *map, int level)
{
	t_link	*link;
	int 	change;
	
	change = 0;
	link = map->all_links_here;
	while(link)
	{
//		if (link->first_room->level == 2 || link->second_room->level == 2)
//			printf("%d\n", 2);
		if (link->checked == 2)
		{
			link = link->next;
			continue;
		}
		if ((link->first_room->level == level &&
			  link->second_room == map->end && link->first_room->from) ||
			 (link->second_room->level == level && link->first_room == map->end && link->second_room->from))
		{
			link->checked = 2;
			if (link->first_room == map->end)
			{
				link->second_room->where = map->end;
				path_is_found(link->second_room, map);
			}
			else if (link->second_room == map->end)
			{
				link->first_room->where = map->end;
				path_is_found(link->first_room, map);
			}
			change = 1;
		}
		else if (link->first_room->level == level && link->second_room->neighbours > 1 &&
		!link->second_room->from && !link->first_room->where && link->first_room->from && link->second_room != map->end &&
		(link->second_room->level - link->first_room->level == 1
		|| link->second_room->level - link->first_room->level == 0))
		{
			link->first_room->where = link->second_room;
			link->second_room->from = link->first_room;
			link->checked = 2;
			change = 1;
		}
		else if (link->second_room->level == level && link->first_room->neighbours > 1 &&
		!link->first_room->from && !link->second_room->where && link->second_room->from && link->first_room != map->end &&
		(link->first_room->level - link->second_room->level == 1 ||
		link->first_room->level - link->second_room->level == 0))
		{
			link->second_room->where = link->first_room;
			link->first_room->from = link->second_room;
			link->checked = 2;
			change = 1;
		}
		
		link = link->next;
	}
	if (change == 0)
	{
		printf("LEVEL %d\n", level);
		return;
	}
	else
	{
		level += 1;
		milky_way(map, level);
	}
}

