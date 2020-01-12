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
#include <stdio.h>

void		*search_necessary_rooms(t_main *map)
{
	t_room	*tmp;
	t_room	*auxiliary;
	int i = 0;


	while (map->start->was_checked != 2)
	{
		tmp = map->start;
		while (tmp)
		{
			auxiliary = map->start;
			while (auxiliary)
			{
				if (check_link(tmp, auxiliary, map->all_links_here) == 1 &&  auxiliary != tmp)
				{
					if ((auxiliary->level - tmp->level <= 1 || auxiliary->level == -1)
						&& (auxiliary->is_part_of_path >= 1 || auxiliary->was_checked == 2)
						&& tmp->is_dead_end != 1)
					{
						printf("checking if: %d: %s - %s;\n ", i,  auxiliary->name, tmp->name);
						if (was_checked(tmp, auxiliary, map->all_links_here) == 1)
						{
							auxiliary->is_part_of_path += 1;
							tmp->was_checked = 2;
							printf("%d: %s - %s;\n ", i,  auxiliary->name, tmp->name);
						}
					}
				}

				auxiliary = auxiliary->next;
			}
			tmp = tmp->next;

		}
		i += 1;
	}
	map->end->is_part_of_path -= 1;
}


void		*search_previous_room(t_main *map, t_room *current)
{
	t_link	*tmp;

	tmp = map->all_links_here;
	while(tmp)
	{
		if (tmp->first_room == current && tmp->second_room->is_dead_end == 0)
		{
			if (tmp->second_room->is_part_of_path == 0)
				tmp->second_room->is_part_of_path = 1;
			else if (tmp->second_room->is_part_of_path > 0)
				tmp->second_room->is_part_of_path += 1;
			break;
		}
		else if (tmp->second_room == current && tmp->first_room->is_dead_end == 0)
		{
			if (tmp->first_room->is_part_of_path == 0)
				tmp->first_room->is_part_of_path = 1;
			else if (tmp->first_room->is_part_of_path > 0)
				tmp->first_room->is_part_of_path += 1;
			break;
		}
		tmp = tmp->next;
	}
}

int 		was_checked(t_room *first, t_room *second, t_link *links)
{
	while (links)
	{
		if ((first == links->first_room && second == links->second_room)
			|| (second == links->first_room && first == links->second_room))
		{
			if (links->checked == 0)
			{
				links->checked = 1;
				printf("checked rooms: %s, %s\n", first->name, second->name);
				return (1);
			}
			return (0);
		}
		else
			links = links->next;
	}
}

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
