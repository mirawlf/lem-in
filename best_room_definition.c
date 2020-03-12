/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   best_room_definition.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samymone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 18:36:18 by samymone          #+#    #+#             */
/*   Updated: 2020/03/11 18:36:21 by samymone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int 			new_or_current(t_room *best, t_room *current)
{
	int 		new;
	int 		old;
	t_room		*tmp;

	new = 1;
	old = 0;
	tmp = best->where;
	while (tmp->where)
	{
		old++;
		tmp = tmp->where;
	}
	tmp = current;
	while (tmp->where)
	{
		new++;
		tmp = tmp->where;
	}
	return (old - new);
}

void			remake_step(t_room *best, t_room *current, t_main *map)
{
	t_link		*link;

	link = map->all_links_here;
	while (link)
	{
		if ((link->first_room == best && link->second_room == current) ||
			(link->second_room == best && link->first_room == current))
			break;
	}
//	free_path(best->where, map);
//	auxiliary(current, best, link, map);
}

t_room			*best_variant4(t_room *current, t_room *variant, t_main *map)
{
	t_link *link;
	t_room *best;

	link = map->all_links_here;
	best = NULL;
	if (variant->level > current->level && variant->inputs > 1)
		return (variant);
	while (link)
	{
		if (ft_strcmp(current->name, link->first_room->name) == 0 ||
			ft_strcmp(current->name, link->second_room->name) == 0)
			printf("STOP\n");
		if (link->first_room == current && link->second_room != variant
			&& !link->second_room->is_dead_end
			&& link->first_room->level < link->second_room->level && link->second_room->inputs > 1
			&& !link->second_room->where)
		{
			best = link->second_room;
			return (link->second_room);
		}
		else if (link->second_room == current && link->first_room != variant
				 && !link->first_room->is_dead_end &&
				 link->first_room->level > link->second_room->level && link->first_room->inputs > 1
				 && !link->first_room->where)
		{
			best = link->first_room;
			return (link->first_room);
		}
		link = link->next;
	}
	if (!best)
		return (variant);
}

t_room			*best_variant3(t_room *current, t_room *variant, t_main *map)
{
	t_link		*link;
	t_room		*best;

	link = map->all_links_here;
	best = NULL;
	if (variant->level == current->level && variant->outputs <= 1)
		return (variant);
	while (link)
	{
		if (ft_strcmp(current->name, link->first_room->name) == 0 || ft_strcmp(current->name, link->second_room->name) == 0)
			printf("STOP\n");
		if (link->first_room == current && link->second_room != variant
			&& link->second_room->outputs == 1 && !link->second_room->is_dead_end
			&& link->first_room->level == link->second_room->level
			&& !link->second_room->where)
		{
			best = link->second_room;
			return (link->second_room);
		}
		else if (link->second_room == current && link->first_room != variant
				 && link->first_room->outputs == 1 && !link->first_room->is_dead_end &&
				 link->first_room->level == link->second_room->level
				 && !link->first_room->where)
		{
			best = link->first_room;
			return (link->first_room);
		}
		link = link->next;
	}
	if (!best)
		return (best_variant4(current, variant, map));
}


t_room			*best_variant2(t_room *current, t_room *variant, t_main *map)
{
	t_link		*link;
	t_room		*best;

	link = map->all_links_here;
	best = NULL;
	if (variant->level < current->level || variant == map->start)
		return (variant);
	while (link)
	{
		if (ft_strcmp(current->name, link->first_room->name) == 0 || ft_strcmp(current->name, link->second_room->name) == 0)
			printf("STOP\n");
		if (link->first_room == current && link->second_room != variant
			&& !link->second_room->is_dead_end
			&& link->first_room->level > link->second_room->level && link->second_room != map->end
			&& !link->second_room->where)
		{
			best = link->second_room;
			return (link->second_room);
		}
		else if (link->second_room == current && link->first_room != variant
				 && !link->first_room->is_dead_end &&
				 link->first_room->level < link->second_room->level && link->first_room != map->end
				 && !link->first_room->where)
		{
			best = link->first_room;
			return (link->first_room);
		}
		link = link->next;
	}
	if (!best)
		return (best_variant3(current, variant, map));
}

t_room			*best_variant(t_room *current, t_room *variant, t_main *map)
{
	t_link		*link;
	t_room		*best;

	best = NULL;
	if ((variant->outputs == 1 && variant->level < current->level)|| variant == map->start)
		return (variant);
	else
	{
		link = map->all_links_here;
		while (link)
		{
			if (ft_strcmp(current->name, link->first_room->name) == 0 || ft_strcmp(current->name, link->second_room->name) == 0)
				printf("STOP\n");
			if (link->first_room == current && link->second_room != variant
				&& link->second_room->outputs == 1 && !link->second_room->is_dead_end
				&& link->first_room->level > link->second_room->level
				&& !link->second_room->where)
			{
				best = link->second_room;
				return (link->second_room);
			}
			else if (link->second_room == current && link->first_room != variant
					 && link->first_room->outputs == 1 && !link->first_room->is_dead_end &&
					 link->first_room->level < link->second_room->level && !link->first_room->where)
			{
				best = link->first_room;
				return (link->first_room);
			}
			link = link->next;
		}
	}
	if (!best)
		return (best_variant2(current, variant, map));
}