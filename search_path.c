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

	curr = map->all_links_here;
	i = 0;
	while (curr)
	{
		if (ft_strcmp(curr->first_room->name, path->name) == 0 || ft_strcmp(curr->second_room->name, path->name) == 0)
			i++;
		curr = curr->next;
	}
	if (!(path->next = (t_path*)ft_memalloc(sizeof(t_path) * i)))
		return (NULL);
	if (i == 1)
		path = remember_next_room(i, map->all_links_here, level, path);
	return (path);
}

t_path		*remember_next_room(int i, t_link *lnk, int level, t_path *path)
{
	t_link	*tmp;

	tmp = lnk;
	while (tmp)
	{
		if (ft_strcmp(tmp->first_room->name, path->name) == 0)
		{
			path->next->name = ft_strdup(tmp->second_room->name);
			return (path);
		}
		tmp = tmp->next;
	}
	return (NULL);
}