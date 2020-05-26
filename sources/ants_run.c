/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_run_like_shit.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 16:41:30 by student           #+#    #+#             */
/*   Updated: 2020/05/20 16:41:32 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int			can_i_go_please(t_room *room)
{
	if (!room->ant)
		return (1);
	return (0);
}

t_ant		*make_normal_step(t_ant *ant, t_main *main)
{
	ant->curr_room->ant = NULL;
	ant->curr_room = ant->curr_room->where;
	print_step(ant->num, ant->curr_room->name, main);
	if (ant->curr_room == main->end)
		return (del_ant(ant, main));
	ant = ant->next;
	return (ant);
}

static int	count_delta(t_path **path_array, int i)
{
	int		delta;
	int		i2;

	delta = 0;
	i2 = i;
	while (i2 > 0)
		delta += (path_array[i]->current->steps -
				path_array[--i2]->current->steps);
	return (delta);
}

static int	choose_way(t_ant *ant, t_path **path_array, int ways_amount,
		int ants_amount)
{
	int		i;
	int		delta;

	i = -1;
	delta = 0;
	while (++i < ways_amount)
	{
		if (i)
			delta = count_delta(path_array, i);
		if (ant->num > delta && ants_amount > delta)
		{
			if (can_i_go_please(path_array[i]->current))
				return (i);
		}
	}
	return (0);
}

int			make_start_step(t_ant *ant, t_main *main)
{
	int		way;

	way = choose_way(ant, main->path_array, main->paths_amount, main->ants);
	if (can_i_go_please(main->path_array[way]->current))
	{
		ant->curr_room = main->path_array[way]->current;
		main->path_array[way]->current->ant = ant;
		print_step(ant->num, main->path_array[way]->current->name, main);
		return (1);
	}
	return (0);
}
