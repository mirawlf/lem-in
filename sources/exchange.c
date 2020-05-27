/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exchange.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 14:12:23 by student           #+#    #+#             */
/*   Updated: 2020/05/27 14:12:25 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	first_if_else(t_path *tmp, t_room *old,
		t_main *map, t_room *new)
{
	if (tmp && tmp->current == old)
		tmp->current = new;
	else
	{
		tmp = map->paths;
		while (tmp->next)
			tmp = tmp->next;
		if (!(tmp->next = (t_path*)ft_memalloc(sizeof(t_path))))
			ft_error("ERROR");
		tmp->next->current = new;
	}
}

static void	second_if_else(t_room *old, t_main *map, t_room *new)
{
	t_path	*start;

	if (old->level == 2)
	{
		start = map->startway->path;
		while (start->current != new)
			start = start->next;
		start->current = old;
	}
	else
	{
		start = map->endway->path;
		while (start->current != old)
			start = start->next;
		start->current = NULL;
		start = map->startway->path;
		while (start->current != new)
			start = start->next;
		start->current = NULL;
	}
}

void		exchange(t_room *current, t_room *variant, t_main *map)
{
	t_room	*old;
	t_room	*new;
	t_path	*tmp;

	old = variant->from;
	old->where = NULL;
	new = current;
	variant->from = current;
	current->where = variant;
	while (old->from)
		old = old->from;
	while (new->from)
		new = new->from;
	tmp = map->paths;
	while (tmp && tmp->current != old)
		tmp = tmp->next;
	first_if_else(tmp, old, map, new);
	second_if_else(old, map, new);
}
