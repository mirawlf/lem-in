/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samymone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 14:19:38 by samymone          #+#    #+#             */
/*   Updated: 2020/02/06 14:19:39 by samymone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void 				lets_go(t_path *best, t_main *map)
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
			map->first_ant->curr_room
		}
	}
}
