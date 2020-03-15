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

static void		second_rooms(t_room *first, t_room *second, t_path *current,
		t_main *map)
{
	t_path		*tmp;

	first->from = second;
	if (!map->paths)
	{
		if (!(map->paths = (t_path *)ft_memalloc(sizeof(t_path))))
			ft_error("malloc failed\n");
		current = map->paths;
		tmp = current;
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
	while (tmp)
	{
		tmp->current->is_part_of_path = 1;
		tmp = tmp->next;
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
