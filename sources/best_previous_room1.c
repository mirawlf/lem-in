/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   best_previous_room1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 14:00:28 by student           #+#    #+#             */
/*   Updated: 2020/05/26 14:00:30 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int		check_details(t_room *room, t_room *variant)
{
	if (room != variant && room->outputs == 1 && !room->is_dead_end
		&& !room->where)
		return (1);
	return (0);
}

t_room			*best_variant(t_room *current, t_room *variant, t_main *map)
{
	t_link		*link;

	if ((variant->outputs == 1 && variant->level < current->level)
		|| variant == map->start)
		return (variant);
	else
	{
		link = map->all_links_here;
		while (link)
		{
			if (link->first_room == current && link->second_room != map->end &&
			check_details(link->second_room, variant) &&
			link->first_room->level > link->second_room->level)
				return (link->second_room);
			else if (link->second_room == current &&
			link->first_room->level < link->second_room->level &&
			link->first_room != map->end &&
			check_details(link->first_room, variant))
				return (link->first_room);
			link = link->next;
		}
	}
	return (best_variant2(current, variant, map));
}
