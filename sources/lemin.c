/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samymone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 16:26:38 by samymone          #+#    #+#             */
/*   Updated: 2020/03/15 22:08:57 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void			tmp_function(t_main	*map)
{
	t_path		*tmp;
	t_room		*room;
	int 		i;

	printf("\nSTARTWAYS:\n");
	i = 1;

	if (map->startway)
	{
		tmp = map->startway->path;
	while (tmp)
	{
		printf("\n%d\n", i);
		room = tmp->current;
		while (room)
		{
			printf("%s ", room->name);
			room = room->where;
		}
		i++;
		tmp = tmp->next;
	}
	}
	if (map->endway
	) {
		tmp = map->endway->path;
		i = 1;
		printf("\nENDWAYS:\n");
		while (tmp) {
			printf("\n%d\n", i);
			room = tmp->current;
			while (room) {
				printf("%s ", room->name);
				room = room->where;
			}
			i++;
			tmp = tmp->next;
		}
	}
	printf("\n\n");
}

void			main_algo_part(t_main *map)
{
	map->start->level = 1;
	map->end->level = -1;
	dead_ends(map);
	next_levels(map, 1);
	count_inputs_and_outputs(map);
	start_searching(map->end, map);
	search_intersections(map);
	count_steps(map);
	if (!(map->path_array = make_path_array(map)))
		ft_error("PATH ARRAYING FAILED IN NECESSARY ROOMS");
	tmp_function(map);
}

int			main(int ac, char **av)
{
	t_main	*map;
	int     flag;

	flag = 0;
	if (ac >= 2)
	{
        if (ac == 3 && !ft_strcmp(av[1], "-p"))
            flag = 3;
        else if (ac == 2)
            flag = 2;
        else
            ft_error("ERROR");
        if (!(map = (t_main *) ft_memalloc(sizeof(t_main))))
            return (-1);
        map->print_paths = flag;
        printf("fd: %d, name: %s\n", map->fd, av[ac - 1]);
        map = parse_input(av, map);
        printf("kewl!\n");
        start_end_link(map);
        main_algo_part(map);
        lets_go(map);
        printf("not kewl!\n");
    }
	else
        ft_error("ERROR");
	return (0);
}
