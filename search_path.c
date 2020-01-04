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

t_path		*pre_algo(t_main *map)
{
	t_path	*path;
	t_path	*extra;

	if (!(path = (t_path*)ft_memalloc(sizeof(t_path))))
		return (NULL);
	extra = path;
	path->name = map->start->name;
	path->x = map->start->x;
	path->y = map->start->y;
	if (map->path == 0)
	{
		map->path += 1;
		path->level = 0;
	}
	path->next = next_step(path, map, path->level);
	path = path->next;
	return (extra);
}


t_path		*next_step(t_path *path, t_main *map, int level)
{
	int 	i;
	t_link	*curr;
	t_path	*next;

	curr = map->all_links_here;
	i = 0;
	while (curr)
	{
		if (ft_strcmp(curr->first_room->name, path->name) == 0)
			i++;
		curr = curr->next;
	}
	if (!(next = (t_path*)ft_memalloc(sizeof(t_path) * i)))
		return (NULL);
	remember_next_rooms(i, map->all_links_here, level, path);
	return (next);
}

t_path		*remember_next_rooms(int i, t_link *links, int level, t_path *path)
{
	int 	j;

	j = 0;
	while(j < i)
	{
		while (links)
		{
			if (ft_strcmp(links->first_room->name, path->name) == 0)
			{
				path->next->name = links->second_room->name;
				path->next++;
			}
			links = links->next;
		}
		j++;
	}
}