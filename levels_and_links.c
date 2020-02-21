/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samymone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 14:55:46 by samymone          #+#    #+#             */
/*   Updated: 2020/02/09 17:14:14 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void		second_rooms(t_room *room, t_main *map)
{
	t_path	*tmp;
	
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

static void	path_is_found(t_room *room, t_main *map)
{
	while (room->from != map->start)
		room = room->from;
	second_rooms(room, map);
}

static	int		aux_for_levels(t_link *link, t_room *first, t_room *second,
		t_main *map)
{
	if (second != map->end)
	{
		second->level = first->level + 1;
		if (!second->from && !first->where && first->from)
		{
			second->from = first;
			first->where = second;
			return (1);
		}
		//link->checked = 1;
	}
	else
	{
		if (first->from && !first->where)
		{
			first->where = map->end;
			map->reached_end += 1;
			path_is_found(first, map);
		}
	}
	return (0);
}

static int		another_room(t_main *map, int checked_room)
{
	t_link		*link;
	
	link = map->all_links_here;
	while(link)
	{
		if (link->first_room->level == map->max_current_level && link->second_room->where == link->first_room)
		{
			link->second_room->where = NULL;
			map->max_current_level--;
			next_levels(map, checked_room);
			if (link->second_room->where)
				return (1);
		}
		else if (link->second_room->level == map->max_current_level && link->first_room->where == link->second_room)
		{
			link->first_room->where = NULL;
			map->max_current_level--;
			next_levels(map, checked_room);
			if (link->first_room->where)
				return (1);
		}
	}
	return (0);
}

///функция, показывающая, есть ли у комнаты сзязи с другими, помимо комнаты уровнем меньше и тупиком

static int	any_valid_rooms(t_room *checked, t_room *known, t_main *map)
{
	int		n;
	t_link	*link;
	
	n = 0;
	link = map->all_links_here;
	while(link)
	{
		if (link->first_room == checked && link->second_room != known && !link->second_room->is_dead_end)
			n++;
		else if (link->second_room == checked &&link->first_room != known && !link->first_room->is_dead_end)
			n++;
		link = link->next;
	}
	if (n > 0)
		return (1);
	return (0);
}

void		next_levels(t_main *map, int checked_rooms)
{
	t_link		*link;
	int			change;
	int			k = 0;

	link = map->all_links_here;
	change = 0;
	while (link)
	{
		if (link->checked)
		{
			link = link->next;
			continue;
		}
		if (link->first_room->level == map->max_current_level && any_valid_rooms(link->second_room, link->first_room, map) == 1 &&
		(!link->second_room->level || link->second_room->level == -1) && (!link->second_room->from &&
		!link->first_room->where))
		{
			checked_rooms += aux_for_levels(link, link->first_room, link->second_room, map);
			change = 1;
			k += 1;
		}
		else if (link->second_room->level == map->max_current_level && any_valid_rooms(link->first_room, link->second_room, map) &&
		(!link->first_room->level || link->first_room->level == -1) && (!link->first_room->from &&
		!link->second_room->where))
		{
			checked_rooms += aux_for_levels(link, link->second_room, link->first_room, map);
			change = 1;
			k += 1;
		}
		link = link->next;
	}
	printf("level: %d, rooms: %d\n", map->max_current_level, k);
	if (change == 0)
	{
		//найти ьакс карент левел, его связь, переделать связь
		
		return ;
	}
	else
	{
		map->max_current_level += 1;
		next_levels(map, checked_rooms);
	}
}

static	void 	dead_ends(t_main *map)
{
	t_room		*rooms;
	t_link		*links;
	
	rooms = map->all_rooms_here;
	links = map->all_links_here;
	while (links)
	{
		links->first_room->neighbours += 1;
		links->second_room->neighbours += 1;
		links = links->next;
	}
	while (rooms)
	{
		if (rooms->neighbours == 1 && rooms != map->start && rooms != map->end)
			rooms->is_dead_end = 1;
		rooms = rooms->next;
	}
}

void			*determine_levels(t_main *map)
{
	t_link		*tmp_link;
	int			checked_rooms;
	
	map->start->level = 1;
	map->end->level = -1;
	tmp_link = map->all_links_here;
	checked_rooms = 0;
	dead_ends(map);
	while (tmp_link)
	{
		if (tmp_link->first_room == map->start && !tmp_link->second_room->is_dead_end)
		{
			tmp_link->second_room->level = 2;
			tmp_link->second_room->from = map->start;
			tmp_link->checked = 1;
			checked_rooms += 1;
		}
		else if (tmp_link->second_room == map->start && !tmp_link->first_room->is_dead_end)
		{
			tmp_link->first_room->level = 2;
			tmp_link->first_room->from = map->start;
			tmp_link->checked = 1;
			checked_rooms += 1;
		}
		tmp_link = tmp_link->next;
	}
	printf("2nd level %d\n map->start %d\n", checked_rooms, map->start_connections);
	map->max_current_level = 2;
	next_levels(map, checked_rooms);
	
	count_steps(map);
	if (!(map->path_array = make_path_array(map)))
		ft_error("PATH ARRAYING FAILED IN NECESSARY ROOMS");
}
