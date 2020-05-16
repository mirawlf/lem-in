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

static void		next_path(int pos, int stp, char *start)
{
	ft_putstr("Path ");
	ft_putnbr(pos);
	ft_putstr(", steps: ");
	ft_putnbr(stp);
	ft_putstr("\n");
	ft_putstr(start);
	ft_putstr(" ");
}

static void		print_paths(t_path **paths, int paths_amount, t_room *start)
{
	int 		i;
	t_room		*room;

	i = 0;
	while (i < paths_amount)
	{
		next_path(i + 1, paths[i]->current->steps + 1, start->name);
		room = paths[i]->current;
		while (room)
		{
			ft_putstr(room->name);
			ft_putstr(" ");
			room = room->where;
		}
		ft_putstr("\n\n");
		i++;
	}
}

static void		sort_paths(t_path **paths, int paths_amount)
{
	int			i;
	t_path		*temp;

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
	sort_paths(result, paths_amount);
	//if (main->print_paths == 1)
	//{
		print_paths(result, paths_amount, main->start);
	//	exit(-1);//проверить на утечки
	//}
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
