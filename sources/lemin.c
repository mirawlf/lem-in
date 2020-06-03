/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 16:58:39 by student           #+#    #+#             */
/*   Updated: 2020/05/20 16:58:41 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void			freeshing(t_main *map)
{
	free_rooms(map->all_rooms_here);
	map->all_rooms_here = NULL;
	free_links(map->all_links_here);
	free(map->line);
	free(map->courier);
	free_paths(map->paths);
	map->paths = NULL;
	if (map->endway)
	{
		free_paths(map->endway->path);
		map->endway = NULL;
	}
	if (map->startway)
	{
		free_paths(map->startway->path);
		map->startway = NULL;
	}
	free_ants(map->first_ant);
	free(map->first_ant);
	map->first_ant = NULL;
	free(map->path_array);
	map->path_array = NULL;
	free_mapfile(map->mapfile);
}

static void		help_function(void )
{
	ft_putstr("\nSpecify, what exactly you want to see:\n\n");
	ft_putstr("\t\tHELP MENU\n");
	ft_putstr("-h\tdisplays help menu and closes programm\n");
	ft_putstr("-p\tdisplays just paths and demanded steps for each one\n");
	ft_putstr("-s\tdisplays ants' steps\n\n");
	exit(1);
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
	print_map(map->mapfile);
}

int				main(int ac, char **av)
{
	t_main		map;
	int			flag;

	flag = 0;
	if (ac > 1)
	{
		if (ac == 2 && !ft_strcmp(av[1], "-p"))
			flag = 1;
		else if (ac == 2 && !ft_strcmp(av[1], "-s"))
			flag = 0;
		else if (ac == 2 && !ft_strcmp(av[1], "-h"))
			help_function();
		else
			ft_error("ERROR");
		//if (!(map = (t_main*)ft_memalloc(sizeof(t_main))))
		//	return (-1);
		map.print_paths = flag;
		parse_input(&map);
		start_end_link(&map);
		main_algo_part(&map);
		lets_go(&map);
		freeshing(&map);
	}
	else
		help_function();
}
