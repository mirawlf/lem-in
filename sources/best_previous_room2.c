/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   best_previous_room2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 14:05:43 by student           #+#    #+#             */
/*   Updated: 2020/05/26 14:05:45 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int		check_details(t_room *room, t_room *variant, t_room *end)
{
	if (room != variant && !room->is_dead_end && room != end)
		return (1);
	return (0);
}

static int		if_first_room_is_current(t_link *link, t_room *variant,
		t_room *end, t_room *current)
{
	if (link->first_room == current &&
	link->first_room->level > link->second_room->level &&
	check_details(link->second_room, variant, end))
		return (1);
	return (0);
}

static int		if_second_room_is_current(t_link *link, t_room *variant,
		t_room *end, t_room *current)
{
	if (link->second_room == current &&
	link->first_room->level < link->second_room->level &&
	check_details(link->first_room, variant, end))
		return (1);
	return (0);
}

t_room			*best_variant2(t_room *current, t_room *variant, t_main *map)
{
	t_link		*link;

	link = map->all_links_here;
	if (variant->level < current->level || variant == map->start)
		return (variant);
	while (link)
	{
		if (if_first_room_is_current(link, variant, map->end, current))
		{
			if (has_already_path(link->second_room, current))
				remake_paths2(link->second_room, current, map);
			else if (!link->second_room->where)
				return (link->second_room);
		}
		else if (if_second_room_is_current(link, variant, map->end, current))
		{
			if (has_already_path(link->first_room, current))
				remake_paths2(link->first_room, current, map);
			else if (!link->first_room->where)
				return (link->first_room);
		}
		link = link->next;
	}
	return (best_variant3(current, variant, map));
}
