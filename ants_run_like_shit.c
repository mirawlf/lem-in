/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_run_like_shit.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 18:57:50 by cyuriko           #+#    #+#             */
/*   Updated: 2020/01/26 18:59:22 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void 	ant_go_to_room(t_ant *ant, t_room *room)
{
	ant->curr_room = room;
	print_step(ant->num, room->name);
}

int 	can_i_go_please(t_room *room)
{
	if (!room->ant)
		return (1);////если в комнате нет муравья
	return (0);////если есть
}

void 	del_ant(t_room *room)
{
	room->ant = NULL;
}

void 	initial_step(t_ant *ant, t_path **path_array, int path_nums)
{

}