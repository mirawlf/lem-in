/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   best_room_definition.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 16:48:07 by student           #+#    #+#             */
/*   Updated: 2020/05/20 16:48:09 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int				compare_paths(t_room *best, t_room *current)
{
	int			old;
	int			new;
	t_room		*tmp;

	old = 0;
	new = 0;
	tmp = best->where;
	while (tmp)
	{
		old++;
		tmp = tmp->where;
	}
	tmp = current;
	while (tmp)
	{
		new++;
		tmp = tmp->where;
	}
	return (old - new);
}

void			remake_paths2(t_room *best, t_room *current, t_main *map)
{
	if (reach_end(current, map->end) == 1)
	{
		free_path(best->where, map);
		best->where = current;
		current->from = best;
		start_searching(map->end, map);
	}
}

int				has_already_path(t_room *room, t_room *current)
{
	if (room->where && compare_paths(room, current) > 0)
		return (1);
	return (0);
}
