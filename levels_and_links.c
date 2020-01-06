/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samymone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 14:55:46 by samymone          #+#    #+#             */
/*   Updated: 2020/01/04 14:55:48 by samymone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		*determine_levels(t_main *map)
{
	t_room	*tmp_room;
	t_link	*tmp_link;

	tmp_room = map->start;
	if (map->path == 0)
	{
		map->path += 1;
		tmp_room->level = 1;
		tmp_room->was_checked = 1;
	}
	while (tmp_room != map->end)
	{
		tmp_link = map->all_links_here;
		while (tmp_link)
		{
			if (ft_strequ(tmp_room->name, tmp_link->first_room->name) == 1
			&& tmp_room->was_checked == 1 && tmp_link->second_room->was_checked == 0)
			{
				tmp_link->second_room->level = tmp_room->level + 1;
				tmp_link->second_room->was_checked += 1;
				map->max_current_level = (map->max_current_level < tmp_link->second_room->level ? tmp_link->second_room->level : map->max_current_level);
			}
			else if (ft_strequ(tmp_room->name, tmp_link->second_room->name) == 1
			&& tmp_room->was_checked == 1 && tmp_link->first_room->was_checked == 0)
			{
				tmp_link->first_room->level = tmp_room->level + 1;
				tmp_link->first_room->was_checked += 1;
				map->max_current_level = (map->max_current_level < tmp_link->first_room->level ? tmp_link->first_room->level : map->max_current_level);
			}
			tmp_link = tmp_link->next;
		}
		tmp_room = tmp_room->next;
	}
	tmp_room->level = -1;
	tmp_room->was_checked += 1;
	except_excess_links(map->all_links_here, map->start);
}

void		*except_excess_links(t_link *links, t_room *rooms)
{
	while (links)
	{
		links->first_room->neighbours += 1;
		links->second_room->neighbours += 1;
		if (links->first_room->level == links->second_room->level)
			links->is_valid = 2;
		links = links->next;
	}
	while (rooms)
	{
		if (rooms->neighbours == 1) //дописать проверку, что комната не старт или энд
			rooms->is_dead_end = 1;
		rooms = rooms->next;
	}
}
