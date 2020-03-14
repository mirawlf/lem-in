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

void			*determine_levels(t_main *map)
{
	map->start->level = 1;
	map->end->level = -1;
	dead_ends(map);
	next_levels(map, 1);
	count_inputs_and_outputs(map);
	start_searching(map->end, map);

	//take_a_glimse_of_paths(map);
	count_steps(map);
	if (!(map->path_array = make_path_array(map)))
		ft_error("PATH ARRAYING FAILED IN NECESSARY ROOMS");
}
