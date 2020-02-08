/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_run_like_shit.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 18:57:50 by cyuriko           #+#    #+#             */
/*   Updated: 2020/02/08 14:24:50 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

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

t_ant 	*make_normal_step(t_ant *ant)
{
	ant->curr_room->ant = NULL;
	ant->curr_room = ant->curr_room->next;
	printf_step(ant->num, ant->curr_room);
	ant = ant->next;
	return (ant);
}