/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant_steps.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 16:38:23 by student           #+#    #+#             */
/*   Updated: 2020/05/20 16:38:25 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_ant		*del_ant(t_ant *ant, t_main *main)
{
	t_ant	*start;

	start = main->first_ant;
	if (ant == start)
	{
		main->first_ant = main->first_ant->next;
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

static int	count_paths(t_path *paths)
{
	int		i;
	t_path	*curr;

	i = 0;
	curr = paths;
	while (curr)
	{
		i++;
		curr = curr->next;
	}
	return (i);
}

static void	sort_path_array(t_path **path_array, int array_size)
{
	int		i;
	t_path	*temp;

	i = 0;
	while (i < array_size)
	{
		if (path_array[i]->current->steps > path_array[i + 1]->current->steps)
		{
			temp = path_array[i];
			path_array[i] = path_array[i + 1];
			path_array[i + 1] = temp;
			i++;
		}
	}
}

void		make_step(t_main *main, t_path **path_array)
{
	t_ant	*ant;

	ant = main->first_ant;
	while (ant != NULL)
	{
		if (!can_i_go_please(ant->curr_room->where) ||
		!make_start_step(ant, main))
			break;
		if (ant->curr_room != main->start &&
		can_i_go_please(ant->curr_room->where))
			ant = make_normal_step(ant, main);
		else if (ant->curr_room == main->start &&
		make_start_step(ant, main))
			ant = ant->next;
		else if (ant->curr_room == main->end && ant->next)
			ant = ant->next;
	}
	ft_putchar('\n');
}
