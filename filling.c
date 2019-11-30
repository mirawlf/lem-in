/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filling.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samymone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 15:21:45 by samymone          #+#    #+#             */
/*   Updated: 2019/11/30 15:21:47 by samymone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/* quant передается значение ants из структуры t_map */

void		ants_fail(int i, t_ant *start, t_map *map)
{
	free_ant(i, start);
	free_map(map);
	ft_error();
}

t_ant		*ant_colony_creation(int quant, t_map *map)
{
	int		i;
	t_ant	*ant;
	t_ant	*prev;

	i = 0;
	while(++i <= quant)
	{
		if (map->start == 1)
		{
			if (!(ant = (t_ant*)malloc(sizeof(t_ant))))
				ants_fail(i, ant, map);
			ant->num = i;
			ant->prev = NULL;
			map->first = ant;
			map->start++;
			if (!(ant->next = (t_ant*)malloc(sizeof(t_ant))))
				ants_fail(i, ant, map);
			prev = ant;
			ant = ant->next;
		}
		else if (map->start == 2)
		{
			ant->num = i;
			if (i == quant)
			{
				map->last = ant;
				ant->next = NULL;
				ant->curr_room = map->current;
				return (ant);
			}
			ant->prev = prev;
			if (!(ant->next = (t_ant*)malloc(sizeof(t_ant))))
				ants_fail(i, map->first, map);
			prev = ant;
			ant = ant->next;
		}
		ant->curr_room = map->current;
	}
	return (NULL);
}
