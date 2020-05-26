/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_tails.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 18:10:04 by student           #+#    #+#             */
/*   Updated: 2020/05/19 18:10:06 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	statement(t_room *current, t_room *possible,
		t_link *link, t_room *end)
{
	if (has_link(current, possible, link)
	&& reach_end(possible, end)
	&& compare_paths(current->where, possible) > 0)
		return (1);
	return (0);
}

static void	new_pointers(t_room *tmp, t_room *current, t_room *possible)
{
	tmp = current->where;
	current->where = possible;
	possible->from = current;
}

static int	found_shorter_path(t_room *current, t_main *map)
{
	t_path	*path;
	t_room	*possible;
	t_room	*tmp;

	if (map->endway)
	{
		path = map->endway->path;
		while (path)
		{
			possible = path->current;
			while (possible)
			{
				if (statement(current, possible, map->all_links_here, map->end))
				{
					new_pointers(tmp, current, possible);
					if (tmp && tmp->from)
						tmp->from = NULL;
					return (1);
				}
				possible = possible->where;
			}
			path = path->next;
		}
	}
	return (0);
}

void		new_tails(t_main *map)
{
	t_path	*path;
	t_room	*current;

	if (map->paths)
	{
		path = map->paths;
		while (path)
		{
			current = path->current;
			while (current->where != map->end)
			{
				if (found_shorter_path(current, map) == 1)
					break ;
				current = current->where;
			}
			path = path->next;
		}
	}
}
