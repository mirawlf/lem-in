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
	t_link	*link;
	t_link	*tmp;

	link = map->all_links_here;
	if (map->all_links_here->first_room->is_dead_end || map->all_links_here->second_room->is_dead_end ||
	map->all_links_here->first_room->level == map->all_links_here->second_room->level)
	{
		tmp = map->all_links_here;
		map->all_links_here = map->all_links_here->next;
		free(tmp);
	}
	else
	{
		tmp = map->all_links_here;
		link = tmp->next;
		while (link)
		{
			if(link->first_room->is_dead_end || link->second_room->is_dead_end ||
			   link->first_room->level == link->second_room->level)
			{
				link->first_room->is_dead_end ? link->second_room->neighbours-- : link->first_room->neighbours--;
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

void		count_inputs_and_outputs(t_main *map)
{
	t_link	*link;

	link = map->all_links_here;
	while(link)
	{
		if (link->first_room == map->end)
		{
			link->first_room->inputs++;
			link->second_room->outputs++;
		}
		else if (link->second_room == map->end)
		{
			link->second_room->inputs++;
			link->first_room->outputs++;
		}
		else if (link->first_room->level < link->second_room->level)
		{
			link->first_room->outputs++;
			link->second_room->inputs++;
		}
		else
		{
			link->second_room->outputs++;
			link->first_room->inputs++;
		}
		link = link->next;
	}
}

