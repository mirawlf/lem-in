/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samymone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 16:26:38 by samymone          #+#    #+#             */
/*   Updated: 2019/12/17 17:10:53 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		ft_error(void)
{
	ft_putendl_fd("Error", 2);
	exit(1);
}

/*
 * здесь считывается нулевая комната и в ней маллочится map->ants
 * количество муравьев, для каждого из которых curr_room приравнивается
 * к порядковому номеру первой комнаты
 */

t_map		*structure_filling(char *line, t_map *map)
{
	if (map->start == 0)
	{
		map->ants = line[0] - '0';
		if (map->ants != ft_atoi(ft_itoa(map->ants)))
		{
			free_map(map);
			ft_error();
		}
		map->start = 1;
		ant_colony_creation(map->ants, map);
	}
	else
	{

	}
	return (map);
}

t_map		*parse_input(char **av, t_map *map)
{
	int		ret;
	char	*line;
	int		fd;

	fd = open(av[1], O_RDONLY);
	ret = 1;
	while (ret == 1)
	{
		ret = get_next_line(fd, &line);
		if (ret == -1)
			ft_error();
		else if (ret == 1)
			structure_filling(line, map);
		else if (ret == 0)
			return (map);
	}
	return (NULL);
}

int			main(int ac, char **av)
{
	t_map	*map;



	if (ac == 2)
	{
		if (!(map = (t_map*)ft_memalloc(sizeof(t_map))))
			return (-1);
		map = parse_input(av, map);
	}
}
