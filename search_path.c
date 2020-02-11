/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samymone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 15:09:34 by samymone          #+#    #+#             */
/*   Updated: 2020/02/06 22:35:57 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include <stdio.h>

void			search_necessary_rooms(t_main *map)
{
	t_room		*tmp;
	t_path		*best_way;

	search_previous_room(map->end, map);
	count_steps(map);
	if (!(map->path_array = make_path_array(map)))
		ft_error("PATH ARRAYING FAILED IN NECESSARY ROOMS");
}

static void		second_rooms(t_room *first, t_room *second, t_path *current,
		t_main *map)
{
	first->from = second;
	if (!map->paths)
	{
		if (!(map->paths = (t_path *)ft_memalloc(sizeof(t_path))))
			ft_error("malloc failed\n");
		current = map->paths;
	}
	else
	{
		current = map->paths;
		while (current->next)
			current = current->next;
		current->next = ft_memalloc(sizeof(t_path));
		current = current->next;
	}
	current->current = first;
}

static void		auxiliary(t_room *first, t_room *second, t_link *link,
		t_main *map)
{
	t_path		*current;

	link->checked = 2;
	if (second->level != 1)
	{
		if (first != map->end)
		{
			if (first->from == NULL && second->where == NULL)
			{
				second->where = first;
				first->from = second;
			}
		}
		else
			second->where = first;
		search_previous_room(second, map);
	}
	else
		second_rooms(first, second, current, map);
}

void			*search_previous_room(t_room *current, t_main *map)
{
	t_link		*link;

	link = map->all_links_here;
	while (current->level == 1 || current->level == -1 ||
	current->where == NULL || current->from == NULL)
	{
		if (link->first_room == current &&
		(link->first_room->level > link->second_room->level ||
		link->first_room->level == -1) && link->checked != 2)
			auxiliary(link->first_room, link->second_room, link, map);
		else if (link->second_room == current &&
		(link->second_room->level > link->first_room->level ||
		link->second_room->level == -1) && link->checked != 2)
			auxiliary(link->second_room, link->first_room, link, map);
		if (link->next)
			link = link->next;
		else
			break ;
	}
}

void			*count_steps(t_main *map)
{
	t_room		*current;
	t_room		*room;
	int			steps;
	t_path		*f;

	f = map->paths;
	while (f)
	{
		steps = 0;
		current = f->current;
		room = current;
		while (current->where)
		{
			steps += 1;
			current = current->where;
		}
		while (room->where)
		{
			room->steps = steps;
			room = room->where;
		}
		f = f->next;
	}
}
