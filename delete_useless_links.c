/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_useless_links.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samymone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 15:52:05 by samymone          #+#    #+#             */
/*   Updated: 2020/02/25 15:52:07 by samymone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		delete_useless_links(t_main *map)
{
	t_link	*tmp;
	t_link	*link;
	t_room	*room;
	
	room = map->all_rooms_here;
	while(room)
	{
		if (room->is_dead_end)
		{
			tmp = map->all_links_here;
			if (map->all_links_here->first_room == room || map->all_links_here->second_room == room)
			{
				tmp = map->all_links_here;
				map->all_links_here = map->all_links_here->next;
				free(tmp);
			}
			else
			{
				tmp = map->all_links_here;
				link = tmp->next;
				while (link && tmp)
				{
					if (link->first_room == room || link->second_room == room)
					{
						link->first_room == room ? link->second_room->neighbours-- : link->first_room->neighbours--;
						tmp->next = link->next;
						link = NULL;
						free(link);
					}
					if (tmp->next)
					{
						tmp = tmp->next;
						link = tmp->next;
					}
					
				}
			}
			
		}
		room = room->next;
	}
}

