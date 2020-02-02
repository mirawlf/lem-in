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

	search_previous_room(map->end, map);
	count_steps(map);
//	if (map->start->is_part_of_path == 1 || map->end->is_part_of_path ==1)
//		go_short_path();
}

void		auxiliary(t_room *first, t_room *second, t_link *link, t_main *map)
{
	t_path	*current;

	first->is_part_of_path += 1;
	link->checked = 1;
	if (second == map->start)
		second->is_part_of_path += 1;
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
}

void		*search_previous_room(t_room *current, t_main *map)
{
	t_link	*link;

	link = map->all_links_here;
	while (current->level == 1 || current->level == -1|| current->where == NULL || current->from == NULL)
	{
		if (!link->checked)
		{
			if (link->first_room == current &&
				(link->first_room->level > link->second_room->level ||
				 link->first_room->level == -1) && link->checked == 0)
				auxiliary(link->first_room, link->second_room, link, map);
			else if (link->second_room == current &&
					 (link->second_room->level > link->first_room->level ||
					  link->second_room->level == -1) && link->checked == 0)
				auxiliary(link->second_room, link->first_room, link, map);
		}
		if (link->next)
			link = link->next;
		else
			break;
	}
}

void		*count_steps(t_main *map)
{
	t_room	*current;
	t_room	*room;
	int		i;
	int		steps;

	i = -1;
	while (++i < map->end->is_part_of_path)
	{
		steps = 0;
		current = map->start;
		while (current->from != map->start || current->was_checked == 2)
			current = current->next;
		room = current;
		while (current->where)
		{
			steps += 1;
			current = current->where;
		}
		while (room->where)
		{
			room->steps = steps;
			room->was_checked = 2;
			room = room->where;
		}
	}
}
