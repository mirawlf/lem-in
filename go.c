/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samymone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 14:19:38 by samymone          #+#    #+#             */
/*   Updated: 2020/02/08 20:03:48 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*void 				lets_go(t_path *best, t_main *map)
{
	t_ant			*colony;
	t_ant			*aux;
	int 			ant;

	colony = ant_colony_creation(map->ants, map);
	ant = -1;
	while (map->last_ant->curr_room != map->end)
	{
		aux = map->first_ant;
		if (map->first_ant->curr_room == map->start)
		{
			map->first_ant->curr_room;
		}
	}
}*/
/*static int go_one_way();//////ЭТО КСТАТИ ПРОВЕРЯЮТ ВОТ ТАК ПРЕКОЛ БЛЯДЬ
{

}*/

static int go_many_ways(t_main *main)
{
	while (main->ants)
		make_step(main, main->path_array);
	ft_error("0 ANTS LEFT HOPE ITS OK");
}

void 		lets_go(t_main *main)
{
	/*if (main->paths_amount == 1 || main->end_connections == 1 || main->start_connections == 1)
		go_one_way();/////take the shortest route
	else*/
		go_many_ways(main);///////do all the cool stuff with different paths
}
