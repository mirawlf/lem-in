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

static int 		read_data(t_main *data)
{
	if (!read_ants(data))
		return (0);
	if (!read_rooms(data))
		return (0);
	if (!data->start || !data->end)
		return (0);
	if (!read_links(data))
		return (0);
	return (1);
}

t_main		*structure_filling(char *line, t_main *map)
{

	if (!read_data(map))
		ft_error("CHTO TO POSHLO NE TAK LOL");//////////check leaks
	ant_colony_creation(map->ants, map);
	ft_strdel(&line);
	return (map);
}

t_main		*parse_input(char **av, t_main *map)
{
	int		ret;
	char	*line;
	int		fd;

	line = NULL;
	map->del_me_fd = open(av[1], O_RDONLY);

		map =	structure_filling(line, map);

//эту всю парашу можно сократить вот этот вот стракчер филлинг на кой он вообще
	return(map);
return (NULL);
}

int			main(int ac, char **av)
{
	t_main	*map;
	t_path	*best;

	if (ac == 2)
	{
		if (!(map = (t_main*)ft_memalloc(sizeof(t_main))))
			return (-1);
		map = parse_input(av, map);
		printf("kewl!\n");
	}
//	check_end_connections(map);
	determine_levels(map);
//	search_paths(map);
//	search_necessary_rooms(map);
	lets_go(map);
	printf ("not kewl!\n");
	return (0);
}
