/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ways_modification.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 18:22:34 by student           #+#    #+#             */
/*   Updated: 2020/05/20 18:22:36 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int			check_length(t_room *current, t_room *prev)
{
	t_room	*tmp;
	int		old;
	int		new;

	old = 0;
	new = 0;
	tmp = current;
	while (tmp)
	{
		new++;
		tmp = tmp->from;
	}
	tmp = prev;
	while (tmp)
	{
		old++;
		tmp = tmp->from;
	}
	return (old - new);
}

int			reach_end(t_room *room, t_room *end)
{
	t_room	*tmp;

	tmp = room;
	while (tmp)
	{
		if (tmp->where == end)
			return (1);
		tmp = tmp->where;
	}
	return (0);
}

static void	else_exchange(t_room *second, t_room *first, t_main *map)
{
	second->from->where = NULL;
	second->from = first;
	first->where = second;
	if (!second->where)
		search_next_room(second, map);
}

void		try_to_change_tails(t_room *current, t_main *map)
{
	t_link	*link;

	link = map->all_links_here;
	while (link)
	{
		if (link->first_room == current && !link->second_room->is_dead_end
		&& check_length(current, link->second_room->from) > 0)
		{
			if (reach_end(link->second_room, map->end) == 1)
				exchange(current, link->second_room, map);
			else
				else_exchange(link->second_room, link->first_room, map);
			break ;
		}
		else if (link->second_room == current && !link->first_room->is_dead_end
		&& check_length(current, link->first_room->from) > 0)
		{
			if (reach_end(link->first_room, map->end) == 1)
				exchange(current, link->first_room, map);
			else
				else_exchange(link->first_room, link->second_room, map);
			break ;
		}
		link = link->next;
	}
}
