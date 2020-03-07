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

static void		second_rooms(t_room *room, t_main *map)
{
	t_path		*tmp;
	
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

static void		path_is_found(t_room *room, t_main *map)
{
	while (room->from != map->start)
		room = room->from;
	second_rooms(room, map);
}

void			next_levels(t_main *map, int max_curr_lvl)
{
	t_link		*link;
	int			change;
	int			k = 0;

	link = map->all_links_here;
	change = 0;
	while (link)
	{
		if (link->checked)
		{
			link = link->next;
			continue;
		}
		if (link->first_room->level == max_curr_lvl && !link->second_room->level)
		{
			link->second_room->level = max_curr_lvl + 1;
			link->checked = 1;
			change = 1;
			k += 1;
		}
		else if (link->second_room->level == max_curr_lvl && !link->first_room->level)
		{
			link->first_room->level = max_curr_lvl + 1;
			link->checked = 1;
			change = 1;
			k += 1;
		}
		link = link->next;
	}
	printf("level: %d, rooms: %d\n", max_curr_lvl, k);
	if (change == 1)
		next_levels(map, max_curr_lvl + 1);
}

static void		dead_ends(t_main *map)
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

void			*determine_levels(t_main *map)
{
	map->start->level = 1;
	map->end->level = -1;
	dead_ends(map);
	next_levels(map, 1);
	count_inputs_and_outputs(map);
	start_searching(map->end, map);
	count_steps(map);
	if (!(map->path_array = make_path_array(map)))
		ft_error("PATH ARRAYING FAILED IN NECESSARY ROOMS");
}
