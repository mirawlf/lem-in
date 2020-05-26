/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   best_next.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 16:47:33 by student           #+#    #+#             */
/*   Updated: 2020/05/20 16:47:35 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_room		*best_room4(t_room *current, t_room *variant, t_main *map)
{
	t_link	*link;

	if (variant->level < current->level && variant != map->start &&
	variant->outputs > 1)
		return (variant);
	else
	{
		link = map->all_links_here;
		while (link)
		{
			if (link->first_room == current && link->second_room != variant
			&& !link->second_room->is_dead_end && link->second_room->outputs > 1
			&& link->second_room->level < link->first_room->level
			&& link->second_room != map->start)
				return (link->second_room);
			else if (link->second_room == current && link->first_room != variant
			&& !link->first_room->is_dead_end && link->first_room->outputs > 1
			&& link->first_room->level < link->second_room->level
			&& link->first_room != map->start)
				return (link->first_room);
			link = link->next;
		}
	}
	return (variant);
}

t_room		*best_room3(t_room *current, t_room *variant, t_main *map)
{
	t_link	*link;

	if (variant->level == current->level && variant->inputs <= 1)
		return (variant);
	else
	{
		link = map->all_links_here;
		while (link)
		{
			if (link->first_room == current && link->second_room != variant
			&& link->second_room->inputs <= 1 && !link->second_room->is_dead_end
			&& link->first_room->level == link->second_room->level
			&& !link->second_room->from)
				return (link->second_room);
			else if (link->second_room == current && link->first_room != variant
			&& link->first_room->inputs <= 1 && !link->first_room->is_dead_end
			&& link->first_room->level == link->second_room->level
			&& !link->first_room->from)
				return (link->first_room);
			link = link->next;
		}
	}
	return (best_room4(current, variant, map));
}

t_room		*best_room2(t_room *current, t_room *variant, t_main *map)
{
	t_link	*link;

	if (variant->level > current->level)
		return (variant);
	else
	{
		link = map->all_links_here;
		while (link)
		{
			if (link->first_room == current && link->second_room != variant
			&& !link->second_room->is_dead_end && !link->second_room->from
			&& link->second_room->level > link->first_room->level)
				return (link->second_room);
			else if (link->second_room == current && link->first_room != variant
			&& !link->first_room->is_dead_end && !link->first_room->from &&
			link->first_room->level > link->second_room->level)
				return (link->first_room);
			link = link->next;
		}
	}
	return (best_room3(current, variant, map));
}

t_room		*best_room(t_room *current, t_room *variant, t_main *map)
{
	t_link	*link;

	if (variant->inputs == 1 && variant->level > current->level)
		return (variant);
	else
	{
		link = map->all_links_here;
		while (link)
		{
			if (link->first_room == current && link->second_room != variant &&
			link->second_room->inputs == 1 && !link->second_room->is_dead_end &&
			!link->second_room->from && link->first_room->level <
			link->second_room->level)
				return (link->second_room);
			else if (link->second_room == current && link->first_room != variant
			&& link->first_room->inputs == 1 && !link->first_room->is_dead_end
			&& !link->first_room->from && link->second_room->level <
			link->first_room->level)
				return (link->first_room);
			link = link->next;
		}
	}
	return (best_room2(current, variant, map));
}
