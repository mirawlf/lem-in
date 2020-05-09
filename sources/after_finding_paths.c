/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samymone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 15:09:34 by samymone          #+#    #+#             */
/*   Updated: 2020/02/06 22:35:57 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"


static void		sort_paths(t_path **paths, int paths_amount, t_room *start)
{
	int			i;
	t_path		*temp;
	t_room		*room;

	if (!paths || !paths_amount)
		ft_error("NO PATHS IN SORTING!");
	i = -1;
	while (++i < (paths_amount - 1))
	{
		if (paths[i]->current->steps > paths[i + 1]->current->steps)
		{
			temp = paths[i];
			paths[i] = paths[i + 1];
			paths[i + 1] = temp;
			i = -1;
		}
	}
	i = 0;
	while (i < paths_amount)
	{
		printf("Path ||%d||, steps: %d\n%s ", i + 1, paths[i]->current->steps + 1, start->name);
		room = paths[i]->current;
		while (room)
		{
			printf("%s ", room->name);
			room = room->where;
		}
		printf("\n\n");
		i++;
	}

}

t_path			**make_path_array(t_main *main)
{
	t_path		*start;
	t_path		**result;
	int			paths_amount;
	int			i;

	i = -1;
	start = main->paths;
	paths_amount = 0;
	while (start)
	{
		paths_amount++;
		start = start->next;
	}
	main->paths_amount = paths_amount;
	start = main->paths;
	if (!(result = (t_path**)ft_memalloc(sizeof(t_path*) * paths_amount)))
		ft_error("FAILED TO ALLOC PATH ARRAY");
	while (++i < paths_amount)
	{
		result[i] = start;
		start = start->next;
	}
	sort_paths(result, paths_amount, main->start);
	return (result);
}


void			count_steps(t_main *map)
{
	t_room		*current;
	t_room		*room;
	int			steps;
	t_path		*f;

	f = map->paths;
	while (f)
	{
		steps = 0;
		current = f->current;
		room = current;
		while (current->where)
		{
			steps += 1;
			current = current->where;
		}
		while (room->where)
		{
			room->steps = steps;
			room = room->where;
		}
		f = f->next;
	}
}
