/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_heads.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 18:10:16 by student           #+#    #+#             */
/*   Updated: 2020/05/19 18:10:19 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		change_path_in_structure(t_room *oldstart,
		t_room *newstart, t_main *map)
{
	t_path	*path;

	path = map->paths;
	while (path)
	{
		if (path->current == oldstart)
		{
			path->current = newstart;
			return ;
		}
		path = path->next;
	}
	path = map->startway->path;
	while (path)
	{
		if (path->current == newstart)
		{
			path->current = oldstart;
			return ;
		}
		path = path->next;
	}
}

int				compare_paths2(t_room *best, t_room *current)
{
	int			old;
	int			new;
	t_room		*tmp;

	old = 0;
	new = 0;
	tmp = best;
	while (tmp)
	{
		new++;
		tmp = tmp->from;
	}
	tmp = current;
	while (tmp)
	{
		old++;
		tmp = tmp->from;
	}
	return (old - new);
}

static int	new_head_found(t_room *start, t_room *current, t_main *map)
{
	t_path	*path;
	t_room	*possible;
	t_room	*start_of_path;

	path = map->paths;
	while (path)
	{
		possible = path->current;
		start_of_path = possible;
		while (possible)
		{
			if (has_link(current, possible, map->all_links_here) && compare_paths2(current, possible->from) > 0)
			{
				possible->from->where = NULL;
				possible->from = current;
				current->where = possible;
				change_path_in_structure(start_of_path, start, map);
				return (1);
			}
			possible = possible->where;
		}
		path = path->next;
	}
	return (0);
}

void		new_heads(t_main *map)
{
	t_path	*path;
	t_room	*room;
	t_room	*start;

	if (map->startway)
	{
		path = map->startway->path;
		{
			while (path)
			{
				if (reach_end(path->current, map->end))
				{
					path = path->next;
					continue ;
				}
				start = path->current;
				room = start;
				while (room)
				{
					if (new_head_found(start, room, map))
						break ;
					room = room->where;
				}
				path = path->next;
			}
		}
	}
}
