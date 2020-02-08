/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filling.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samymone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 15:21:45 by samymone          #+#    #+#             */
/*   Updated: 2020/02/08 20:09:14 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/* quant передается значение ants из структуры t_map */

void		ants_fail(int i, t_ant *start, t_main *map)
{
//	free_ant(i, start);
//	free_map(map);
	ft_error("ERROR: SOMETHING WRONG WITH ANTS");
}

t_ant		*ant_colony_creation(int quant, t_main *map)
{
	int i;
	t_ant *ant;

	i = -1;
	while (++i < quant)
	{
		if (!i)
		{
			if (!(ant = (t_ant*)ft_memalloc(sizeof(t_ant))))
				ft_error("ANTS FAILED to ALLOC");
			map->first_ant = ant;
		}
		ant->num = quant - i;
		if ((i + 1) == quant)
		{
			map->last_ant = ant;
			return (map->start);
		}
		else if (!(ant->next = (t_ant*)ft_memalloc(sizeof(t_ant))))
			ft_error("ANTS FAILED to ALLOC");
//			ants_fail(i, map->first_ant, map);
	//	ant->next->prev = ant;////////////////////////надо ли это?
		ant->curr_room = map->start;
		ant = ant->next;
	}
	return (NULL);
}