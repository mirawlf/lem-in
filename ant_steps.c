/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant_steps.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 16:47:04 by cyuriko           #+#    #+#             */
/*   Updated: 2020/02/01 17:01:40 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int 	count_paths(t_path *paths)
{
	int i = 0;
	t_path	*curr;

	curr = paths;

	while (curr)
	{
		i++;
		curr = curr->next;
	}
	return (i);
}

static void sort_path_array(t_path **path_array, int array_size)
{
	int i;
	t_path *temp;

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

void	init_walkthrough(t_main *main)
{
	int	paths;
	int i;
	t_path *curr;

	i = -1;
	curr = main->paths;
	t_path	**path_array;

	paths = count_paths(main->paths);
	if (!paths)
		ft_error("FAILED TO FIND VALID PAthS TO MOVE EM ANTS");
	if (!(path_array = (t_path**)ft_memdel(sizeof(t_path) * paths)))
		ft_error("faild to alloc memory for paths array");
	while (++i < paths)
	{
		path_array[i] = curr;
		curr = curr->next;
	}
	sort_path_array(path_array, paths);
}

int		make_step(t_ant *ant, t_path **path_array)
{
	
}