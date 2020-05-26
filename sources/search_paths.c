/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_paths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 17:53:20 by student           #+#    #+#             */
/*   Updated: 2020/05/20 17:53:22 by student          ###   ########.fr       */
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

int			first_check_for_searching(t_room *current, t_link *link,
		t_main *map)
{
	if (link->first_room == current)
	{
		if (!link->second_room->is_dead_end && link->checked != 2 &&
		!link->second_room->where && link->second_room->level != -1 &&
		best_variant(link->first_room, link->second_room, map) ==
		link->second_room)
			return (1);
	}
	return (0);
}

int			second_check_for_searching(t_room *current, t_link *link,
		t_main *map)
{
	if (link->second_room == current)
	{
		if (!link->first_room->is_dead_end && !link->first_room->where
		&& link->checked != 2 && link->first_room->level != -1 &&
		best_variant(link->second_room, link->first_room, map) ==
		link->first_room)
			return (1);
	}
	return (0);
}

void		search_previous_room(t_room *current, t_main *map)
{
	t_link	*link;

	link = map->all_links_here;
	while (current->level == 1 || !current->where || !current->from)
	{
		if (first_check_for_searching(current, link, map))
		{
			auxiliary(link->first_room, link->second_room, link, map);
			break ;
		}
		else if (second_check_for_searching(current, link, map))
		{
			auxiliary(link->second_room, link->first_room, link, map);
			break ;
		}
		if (link->next)
			link = link->next;
		else if (!current->from)
		{
			remake_paths(current, map);
			break ;
		}
	}
	start_searching(map->end, map);
}

static int	tmp_statement(t_room *current, t_room *another, t_room *end)
{
	if (current == end && !another->where && another->level)
		return (1);
	return (0);
}

void		start_searching(t_room *room, t_main *map)
{
	t_link	*link;
	t_room	*tmp;

	tmp = NULL;
	link = map->all_links_here;
	while (link)
	{
		if (tmp_statement(link->first_room, link->second_room, map->end))
		{
			if (!tmp || tmp->level > link->second_room->level)
				tmp = link->second_room;
		}
		else if (tmp_statement(link->second_room, link->first_room, map->end))
		{
			if (!tmp || tmp->level > link->first_room->level)
				tmp = link->first_room;
		}
		link = link->next;
	}
	if (tmp)
	{
		tmp->where = map->end;
		search_previous_room(tmp, map);
	}
}
