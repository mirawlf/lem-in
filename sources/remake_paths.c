/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remake_paths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 17:46:14 by student           #+#    #+#             */
/*   Updated: 2020/05/20 17:46:16 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void		zero_statement(t_link *link, t_room *current, t_room *next)
{
	if ((link->first_room == current && link->second_room == next)
		|| (link->first_room == next && link->second_room == current))
		link->checked = 1;
}

static int		first_statement(t_link *link, t_main *map,
		t_room *next, t_room *current)
{
	if (link->first_room == next && link->second_room != current &&
	!link->second_room->is_dead_end && link->second_room->level != -1 &&
	link->checked != 2 && !link->second_room->where &&
	best_variant(link->first_room, link->second_room, map) == link->second_room)
		return (1);
	return (0);
}

static int		second_statement(t_link *link, t_main *map,
		t_room *next, t_room *current)
{
	if (link->second_room == next && link->first_room != current &&
	!link->first_room->is_dead_end && link->first_room->level != -1 &&
	link->checked != 2 && !link->first_room->where &&
	best_variant(link->second_room, link->first_room, map) == link->first_room)
		return (1);
	return (0);
}

static void		link_checked(t_link *link, t_room *next,
		t_room *current, t_main *map)
{
	if (next && !next->from)
	{
		next->from = current;
		link = map->all_links_here;
		if ((link->first_room == current && link->second_room == next)
		|| (link->first_room == next && link->second_room == current))
			link->checked = 2;
	}
	possible_ways(current, map);
}

void			remake_paths(t_room *current, t_main *map)
{
	t_room		*next;
	t_link		*link;

	next = current->where;
	link = map->all_links_here;
	if (next)
		next->from = NULL;
	while (link)
	{
		zero_statement(link, current, next);
		if (first_statement(link, map, next, current))
		{
			current->where = NULL;
			auxiliary(link->first_room, link->second_room, link, map);
			break ;
		}
		else if (second_statement(link, map, next, current))
		{
			current->where = NULL;
			auxiliary(link->second_room, link->first_room, link, map);
			break ;
		}
		link = link->next;
	}
	link_checked(link, next, current, map);
}
