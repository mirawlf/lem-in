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

t_map		*parse_input(char **av, t_map *map)
{
	
}

int			main(int ac, char **av)
{
	t_map	*map;

	if (ac == 1)
	{
		if (!(map = (t_map*)malloc(sizeof(t_map))))
			return(0);
		map = parse_input(av, map);
	}
}
