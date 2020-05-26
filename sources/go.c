/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 16:55:12 by student           #+#    #+#             */
/*   Updated: 2020/05/20 16:55:14 by student          ###   ########.fr       */
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

static void		go_one_way(t_main *main)
{
	int			i;
	t_path		*best_way;

	i = 0;
	best_way = shortest_way(main->paths);
	while (main->ants)
	{
		++i;
		make_oneway_step(main, best_way);
	}
	ft_putstr("\nNumber of lines: ");
	ft_putnbr(i);
	ft_putstr("\n");
	ft_error("0 ANTS LEFT HOPE ITS OK");
}

static void		go_many_ways(t_main *main)
{
	int			i;

	i = 0;
	while (main->ants)
	{
		++i;
		make_step(main, main->path_array);
	}
	ft_putstr("\nNumber of lines: ");
	ft_putnbr(i);
}

void			lets_go(t_main *main)
{
	if (main->paths_amount == 1 || main->end_connections == 1
	|| main->start_connections == 1)
		go_one_way(main);
	else
		go_many_ways(main);
}
