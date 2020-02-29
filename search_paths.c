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
	t_link *link;

	link = map->all_links_here;
	while (current->level == 1 || current->level == -1 ||
		   current->where == NULL || current->from == NULL)
	{
		if (link->first_room == current &&
			(link->first_room->level > link->second_room->level ||
			 link->first_room->level == -1) && link->checked != 2)
			auxiliary(link->first_room, link->second_room, link, map);
		else if (link->second_room == current &&
				 (link->second_room->level > link->first_room->level ||
				  link->second_room->level == -1) && link->checked != 2)
			auxiliary(link->second_room, link->first_room, link, map);
		if (link->next)
			link = link->next;
		else
			break;
	}
}