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
		ant->curr_room = map->start;
		if ((i + 1) == quant)
			return (map->start);
		if (!(ant->next = (t_ant*)ft_memalloc(sizeof(t_ant))))
			ft_error("ANTS FAILED to ALLOC");
		ant = ant->next;
	}
	return (NULL);
}