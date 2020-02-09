/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_run_like_shit.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 18:57:50 by cyuriko           #+#    #+#             */
/*   Updated: 2020/02/09 14:16:38 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int 	can_i_go_please(t_room *room)///////пройтись по функциям, я эту хуйню как минимум в старт степе проверяю лишний раз, а вот надо ли?
{
	if (!room->ant)
		return (1);////если в комнате нет муравья
	return (0);////если есть
}

t_ant 	*del_ant(t_ant *ant, t_main *main)
{
	////////////will be like this for now/////will optimize later if required
	t_ant *start;

	start = main->first_ant;
	if (ant == start)
	{
		main->first_ant = main->first_ant->next;/////////////тут везде сеги вылезут лол
		ft_memdel((void*)&ant);
		ant = main->first_ant;
	}
	else
	{
		while (start->next != ant)
			start = start->next;
		if (ant->next)
			start->next = ant->next;
		ft_memdel((void*)&ant);
		ant = start->next;
	}
	main->ants--;
	return (ant);
}

t_ant 	*make_normal_step(t_ant *ant, t_main *main)
{
	ant->curr_room->ant = NULL;
	ant->curr_room = ant->curr_room->where;
	print_step(ant->num, ant->curr_room->name, main);
	if (ant->curr_room == main->end)
	{
		ant = del_ant(ant, main);
		return (ant);/////////сразу ретернить дел ант надо
	}
	ant = ant->next;
	return (ant);
}

static int	count_delta(t_path **path_array, int i)
{
	int delta = 0;
	int i2;
	i2 = i;

	while (i2 > 0)
		delta += (path_array[i]->current->steps - path_array[--i2]->current->steps);
	return (delta);
}

static int choose_way(t_ant *ant, t_path **path_array, int ways_amount, int ants_amount)
{
	int i;
	int delta = 0;

	i = -1;
	while (++i < ways_amount)
	{
		if (i)
			delta = count_delta(path_array, i);
		if (ant->num > delta && ants_amount > delta)/////ants amount may be excessive?
		{
			if (can_i_go_please(path_array[i]->current))
				return (i);
		}
	}
	return (0);
}

int 	make_start_step(t_ant *ant, t_main *main)
{
	int	way;

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