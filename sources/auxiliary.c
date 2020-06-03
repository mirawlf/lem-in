/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliary.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 20:49:18 by student           #+#    #+#             */
/*   Updated: 2020/06/03 20:49:20 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		auxiliary(t_room *first, t_room *second, t_link *link, t_main *map)
{
	if (second->level != 1)
	{
		if (first != map->end)
		{
			if (first->from == NULL && second->where == NULL)
			{
				second->where = first;
				first->from = second;
				link->checked = 2;
			}
		}
		else
		{
			second->where = first;
			link->checked = 2;
		}
		search_previous_room(second, map);
	}
	else
		second_rooms(first, map);
}

t_room		*new_next_room(t_room *current, t_path *ends, t_link *linklist)
{
	t_path	*path;
	t_room	*room;

	path = ends;
	while (path)
	{
		room = path->current;
		while (room)
		{
			if (has_link(current, room, linklist))
				return (room);
			room = room->where;
		}
		path = path->next;
	}
	return (NULL);
}

t_room		*new_prev_room(t_room *current, t_path *starts, t_link *linklist)
{
	t_path	*path;
	t_room	*room;

	path = starts;
	while (path)
	{
		room = path->current;
		while (room)
		{
			if (has_link(current, room, linklist))
				return (room);
			room = room->where;
		}
		path = path->next;
	}
	return (NULL);
}

void		free_path(t_room *current, t_main *map)
{
	t_room	*tmp;

	while (current && current->where != map->end)
	{
		if (current)
		{
			if (current->where)
				current->where->from = NULL;
		}
		tmp = current->where;
		current->where = NULL;
		current->from = NULL;
		current = tmp;
	}
	if (current)
		current->from = NULL;
}
