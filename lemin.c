/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samymone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 16:26:38 by samymone          #+#    #+#             */
/*   Updated: 2019/12/22 17:13:51 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		ft_error(char *error)
{
	ft_putendl_fd(error, 2);
	exit(1);
}

/*
 * здесь считывается нулевая комната и в ней маллочится map->ants
 * количество муравьев, для каждого из которых curr_room приравнивается
 * к порядковому номеру первой комнаты
 */

t_main		*structure_filling(char *line, t_main *map, int fd)
{
//	if (map->start == 0)
//	{
	map->ants = ft_atoi(line);////////стоит чекнуть коммент
	//	if (map->ants != ft_atoi(ft_itoa(map->ants)))
	//	{
	//		free_map(map);
	//		ft_error();
	//	}
	//	map->start = 1;

	map->all_rooms_here = read_rooms(map, fd);
	map->all_links_here = get_me_links(map, fd, map->all_rooms_here);
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
	fd = open(av[1], O_RDONLY);
	ret = 1;
		ret = get_next_line(fd, &line);
		if (ret == -1)
			ft_error("ERROR: DON'T TRY TO SEGV ME");///////////убрать проверку на рид == -1 в дальнейших проверках, если это не уберем, этой проверки достаточно
		else if (ret == 1)
			structure_filling(line, map, fd);
		else if (ret == 0)
			return (map);
//	}
if (map)
	return(map);
return (NULL);
}

int			main(int ac, char **av)
{
	t_main	*map;



	if (ac == 2)
	{
		if (!(map = (t_main*)ft_memalloc(sizeof(t_main))))
			return (-1);
		map = parse_input(av, map);
		printf("kewl!\n");
	}
	printf ("not kewl!\n");
	return (0);
}
