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

static void		auxiliary(t_room *first, t_room *second, t_link *link,
							 t_main *map)
{
	t_path		*current;


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

void			search_previous_room(t_room *current, t_main *map)
{
	t_link		*link;
	t_link		*extra;
	t_room		*tmp;

	tmp = NULL;
	link = map->all_links_here;
	while (current->level == 1 /*|| current->level == -1*/ ||
		   current->where == NULL || current->from == NULL)
	{
		if (link->first_room == current &&
			(link->first_room->level > link->second_room->level &&
			 link->second_room->level != -1) && link->checked != 2)
		{
			auxiliary(link->first_room, link->second_room, link, map);
			break;
		}
		else if (link->second_room == current &&
				 (link->second_room->level > link->first_room->level &&
				  link->first_room->level != -1) && link->checked != 2)
		{
			auxiliary(link->second_room, link->first_room, link, map);
			break;
		}
		if (link->next)
			link = link->next;
		else
			break;
	}
	if (map->end_connections)
		start_searching(map->end, map);
}

void			start_searching(t_room *room, t_main *map)
{
	t_link		*link;
	t_room		*tmp;

	tmp = NULL;
	link = map->all_links_here;
	while(link)
	{
		if (link->first_room == map->end && !link->second_room->where)
		{
			if (!tmp || tmp->level > link->second_room->level)
				tmp = link->second_room;
		}
		else if (link->second_room == map->end && !link->first_room->where)
		{
			if (!tmp || tmp->level > link->first_room->level)
				tmp = link->first_room;
		}
		link = link->next;
	}
	if (tmp)
		map->end_connections--;
	tmp->where = map->end;
	search_previous_room(tmp, map);
}