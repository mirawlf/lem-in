/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samymone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 15:09:34 by samymone          #+#    #+#             */
/*   Updated: 2020/01/06 15:09:36 by samymone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		*search_necessary_rooms(t_main *map)
{
	t_room	*tmp;

	search_previous_room(map, map->end);
//	while (map->start->is_part_of_path != 1)
//	{
//		tmp = map->start;
//		while (tmp->is_part_of_path != 1)
//			tmp
//	}
}

void		*search_previous_room(t_main *map, t_room *current)
{
	t_link	*tmp;

	tmp = map->all_links_here;
	while(tmp)
	{
		if (tmp->first_room == current && tmp->second_room->is_dead_end == 0
		&& tmp->second_room->is_part_of_path == 0)
			tmp->second_room->is_part_of_path = 1;
		else if (tmp->second_room == current && tmp->first_room->is_dead_end == 0
		&& tmp->first_room->is_part_of_path == 0)
			tmp->first_room->is_part_of_path = 1;
		tmp = tmp->next;
	}
}

//{
//	t_room	*tmp;
//	t_path	*extra;
//
//	extra = path;
//	extra->current = map->start;
//	tmp = map->start->next;
//	while (tmp)
//	{
//		if ((tmp->level - extra->current->level == 1 || tmp->level == -1)
//		&& check_link(tmp, extra->current, map->all_links_here) == 1)
//		{
//			if (!(extra->next = (t_path*)ft_memalloc(sizeof(t_path))))
//				return (-1);
//			extra->next->current = tmp;
//			if (tmp->level == -1)
//			{
//				extra->next->next = NULL;
//				return (path);
//			}
//			else
//				extra = extra->next;
//		}
//		tmp = tmp->next;
//	}
//	return (NULL);
//}

int			check_link(t_room *first, t_room *second, t_link *links)
{
	while (links)
	{
		if ((first == links->first_room && second == links->second_room)
			|| (second == links->first_room && first == links->second_room))
			return (1);
		else
			links = links->next;
	}
	return (0);
}
