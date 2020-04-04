/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_paths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samymone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 16:16:03 by samymone          #+#    #+#             */
/*   Updated: 2020/03/08 16:16:05 by samymone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void			second_rooms(t_room *room, t_main *map)
{
	t_path		*tmp;

	if (!map->paths)
	{
		if (!(map->paths = (t_path *)ft_memalloc(sizeof(t_path))))
			ft_error("malloc failed\n");
		map->paths->current = room;
	}
	else
	{
		tmp = map->paths;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = (t_path *)ft_memalloc(sizeof(t_path));
		tmp = tmp->next;
		tmp->current = room;
	}
}

void            possible_ways(t_room *room, t_main *map)
{
    t_path     *tmp;

    if (!map->endway)
    {
        if (!(map->endway = (t_toend*)ft_memalloc(sizeof(t_toend)))
        || !(map->endway->path = (t_path*)ft_memalloc(sizeof(t_path))))
            ft_error("malloc failed\n");
        map->endway->path->current = room;
    }
    else
    {
        tmp = map->endway->path;
        while(tmp->next)
            tmp = tmp->next;
        tmp->next = (t_path*)ft_memalloc(sizeof(t_path));
        tmp = tmp->next;
        tmp->current = room;
    }
}

static void		path_is_found(t_room *room, t_main *map)
{
	while (room->from != map->start)
		room = room->from;
	second_rooms(room, map);
}

static void		auxiliary(t_room *first, t_room *second, t_link *link,
		t_main *map)
{
	if (second->level != 1)
	{
		if (first != map->end)
		{
			if (first->from == NULL && second->where == NULL)
			{
				second->where = first;
				first->from = second;
				link->checked = 2;
			}
		}
		else
		{
			second->where = first;
			link->checked = 2;
		}
		search_previous_room(second, map);
	}
	else
		second_rooms(first, map);
}

void			free_path(t_room *current, t_main *map)
{
	t_room		*tmp;

	while (current && current->where != map->end)
	{
		if (current)
		{
			if (current->where)
				current->where->from = NULL;
		}
		tmp = current->where;
		current->where = NULL;
		current->from = NULL;
		current = tmp;
	}
	if (current)
		current->from = NULL;
}

void			remake_paths(t_room *current, t_main *map)
{
	t_room		*next;
	t_link		*link;

	next = current->where;
	link = map->all_links_here;
	next->from = NULL;
	while (link)
	{
		if ((link->first_room == current && link->second_room == next)
		|| (link->first_room == next && link->second_room == current))
			link->checked = 1;
		if (link->first_room == next && link->second_room != current && !link->second_room->is_dead_end
		&& link->second_room->level != -1 && link->checked != 2 && !link->second_room->where
		&& best_variant(link->first_room, link->second_room, map) == link->second_room)
		{
			current->where = NULL;
			auxiliary(link->first_room, link->second_room, link, map);
			break ;
		}
		else if (link->second_room == next && link->first_room != current && !link->first_room->is_dead_end
		&& link->first_room->level != -1 && link->checked != 2 && !link->first_room->where
		&& best_variant(link->second_room, link->first_room, map) == link->first_room)
		{
			current->where = NULL;
			auxiliary(link->second_room, link->first_room, link, map);
			break ;
		}
		link = link->next;
	}
	if (!next->from)
    {
	    next->from = current;
	    link = map->all_links_here;
	    if ((link->first_room == current && link->second_room == next)
	    || (link->first_room == next && link->second_room == current))
	        link->checked = 2;
        possible_ways(current, map);
    }
}

int				first_check_for_searching(t_room *current, t_link *link,
		t_main *map)
{
	if (link->first_room == current)
	{
		if (!link->second_room->is_dead_end && link->checked != 2 &&
		!link->second_room->where && link->second_room->level != -1 &&
		best_variant(link->first_room, link->second_room, map) ==
		link->second_room)
			return (1);
	}
	return (0);
}

int				second_check_for_searching(t_room *current, t_link *link,
		t_main *map)
{
	if (link->second_room == current)
	{
		if (!link->first_room->is_dead_end && !link->first_room->where
		&& link->checked != 2 && link->first_room->level != -1 &&
		best_variant(link->second_room, link->first_room, map) ==
		link->first_room)
			return (1);
	}
	return (0);
}

void			search_previous_room(t_room *current, t_main *map)
{
	t_link		*link;

	link = map->all_links_here;
	while (current->level == 1 ||
	current->where == NULL || current->from == NULL)
	{
		if (first_check_for_searching(current, link, map))
		{
			auxiliary(link->first_room, link->second_room, link, map);
			break ;
		}
		else if (second_check_for_searching(current, link, map))
		{
			auxiliary(link->second_room, link->first_room, link, map);
			break ;
		}
		if (link->next)
			link = link->next;
		else if (!current->from)
		{
			remake_paths(current, map);
			break ;
		}
	}
	start_searching(map->end, map);
}

void			start_searching(t_room *room, t_main *map)
{
	t_link		*link;
	t_room		*tmp;

	tmp = NULL;
	link = map->all_links_here;
	while (link)
	{
		if (link->first_room == map->end && !link->second_room->where && link->second_room->level)
		{
			if (!tmp || tmp->level > link->second_room->level)
				tmp = link->second_room;
		}
		else if (link->second_room == map->end && !link->first_room->where && link->first_room->level)
		{
			if (!tmp || tmp->level > link->first_room->level)
				tmp = link->first_room;
		}
		link = link->next;
	}
	if (tmp)
	{
		tmp->where = map->end;
		search_previous_room(tmp, map);
	}
}
