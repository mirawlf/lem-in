/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_passageway.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 16:55:50 by student           #+#    #+#             */
/*   Updated: 2020/05/20 16:55:53 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		startway_minimize(t_room *current, t_path *starts)
{
	t_path	*path;

	path = starts;
	while (path->current != current)
		path = path->next;
	path->current = NULL;
}

void		split_path(t_room *current, t_room *next, t_room *prev, t_main *map)
{
	t_room	*tmp;

	tmp = current->where;
	current->where = next;
	next->from = current;
	while (!has_link(tmp, prev, map->all_links_here))
		tmp = tmp->where;
	tmp->from = prev;
	prev->where = tmp;
	while (tmp->from)
		tmp = tmp->from;
	startway_minimize(tmp, map->startway->path);
	second_rooms(tmp, map);
}

static void	new_next_prev_room(t_main *map, t_room *room,
		t_room *new_next, t_room *new_prev)
{
	t_room	*room2;

	new_next = NULL;
	new_prev = NULL;
	if ((new_next = new_next_room(room, map->endway->path,
			map->all_links_here)))
	{
		room2 = room->where;
		while (room2)
		{
			if ((new_prev = new_prev_room(room2, map->startway->path,
					map->all_links_here)))
			{
				split_path(room, new_next, new_prev, map);
				break ;
			}
			room2 = room2->where;
		}
	}
}

void		number_of_path_increasing(t_main *map)
{
	t_path	*path;
	t_room	*room;
	t_room	*new_next;
	t_room	*new_prev;

	path = map->paths;
	while (path)
	{
		room = path->current;
		while (room)
		{
			new_next_prev_room(map, room, new_next, new_prev);
			if (new_next && new_prev)
				break ;
			room = room->where;
		}
		if (new_next && new_prev)
			break ;
		path = path->next;
	}
}
