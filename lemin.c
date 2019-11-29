/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samymone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 16:26:38 by samymone          #+#    #+#             */
/*   Updated: 2019/10/27 16:26:40 by samymone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		ft_error(void)
{
	ft_putendl_fd("Error", 2);
	exit(1);
}

t_map		*structure_filling(char *line, t_map *map)
{
	if (map->start == 0)
	{
		map->ants = line[0] - '0';
		map->start = 1;
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
		if (!(map = (t_map*)malloc(sizeof(t_map))))
			return (0);
		ft_bzero(map, sizeof(t_map));
		map = parse_input(av, map);
	}
}
