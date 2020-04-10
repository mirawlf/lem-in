/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samymone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 14:19:38 by samymone          #+#    #+#             */
/*   Updated: 2020/02/09 16:13:24 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static t_path	*shortest_way(t_path *paths)
{
	t_path		*tmp;
	t_path		*actual;

	tmp = paths;
	actual = paths;
	while (tmp)
	{
		if (tmp->current->steps < actual->current->steps)
			actual = tmp;
		tmp = tmp->next;
	}
	return (actual);
}

static int go_one_way(t_main *main)//////ЭТО КСТАТИ ПРОВЕРЯЮТ ВОТ ТАК ПРЕКОЛ БЛЯДЬ
{
	int i = 0; //////testiing lines
	t_path *best_way = shortest_way(main->paths);
	while (main->ants)
	{
		++i;
		make_oneway_step(main, best_way);
	}
	printf("lines ||%d||\n", i);
	ft_error("0 ANTS LEFT HOPE ITS OK");
}

static int	go_many_ways(t_main *main)
{
	int		i = 0; //////testiing lines

	while (main->ants)
	{
		++i;
		make_step(main, main->path_array);

	}
	printf("lines ||%d||\n", i);
	ft_error("0 ANTS LEFT HOPE ITS OK");
}

void 		lets_go(t_main *main)
{
	if (main->paths_amount == 1 || main->end_connections == 1 || main->start_connections == 1)
		go_one_way(main);/////take the shortest route
	else
		go_many_ways(main);///////do all the cool stuff with different paths
}
