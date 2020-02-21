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

static void	search_end(t_main *map, int max_room_level)
{
	t_link	*link;
	
	link = map->all_links_here;
	while(link)
	{
		if (link->first_room->level == max_room_level && link->second_room != map->start &&
		link->first_room->from && !link->first_room->where && !link->second_room->from)
		{
			if (link->second_room == map->end)
			{
				link->first_room->where = map->end;
				path_is_found(link->first_room, map);
			}
			else
			{
				link->first_room->where = link->second_room;
				link->second_room->from = link->first_room;
			}

		}
		else if (link->second_room->level == max_room_level && link->first_room != map->start &&
		link->second_room->from && !link->second_room->where && !link->first_room->from)
		{
			if (link->first_room == map->end)
			{
				link->second_room->where = map->end;
				path_is_found(link->second_room, map);
			}
			else
			{
				link->second_room->where = link->first_room;
				link->first_room->from = link->second_room;
			}
	
		}
		link = link->next;
	}
	
	if (max_room_level < map->max_current_level + 1)
	{
		max_room_level += 1;
		search_end(map, max_room_level);
	}
}

void 		search_paths(t_main *map)
{
	t_link	*link;
	int 	max_room_level;
	
	link = map->all_links_here;
	while(link)
	{
		if (link->first_room == map->start)
			link->second_room->from = map->start;
		else if (link->second_room == map->start)
			link->first_room->from = map->start;
		link = link->next;
	}
	max_room_level = 2;
	search_end(map, max_room_level);
	count_steps(map);
	if (!(map->path_array = make_path_array(map)))
		ft_error("PATH ARRAYING FAILED IN NECESSARY ROOMS");
}
