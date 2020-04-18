#include "lemin.h"

void		delete_this_path(t_main *map, t_path *path)
{
	t_path	*tmp;

	if (map->endway->path == path)
	{
		//free(path);
		ft_memdel((void*)path);
		map->endway->path = map->endway->path->next;
	}
	else
	{
		tmp = map->endway->path;
		while (tmp->next != path)
			tmp = tmp->next;
		tmp->next = path->next;
		//free(path);
		ft_memdel((void*)path);
	}
}

int 		has_link(t_room *current, t_room *possible, t_main *map)
{
	t_link	*link;

	link = map->all_links_here;
	while (link)
	{
		if ((link->first_room == current && link->second_room == possible)
		|| (link->second_room == current && link->first_room == possible))
			return (1);
		link = link->next;
	}
	return (0);
}

int 		path_found(t_room *room, t_main *map)
{
	t_room	*current;
	t_path	*path;
	t_room	*possible;

	current = room;
//	if (map->endway->path)
//	{
		path = map->endway->path;
		while (path)
		{
			possible = path->current;
			while (possible)
			{
				if (has_link(current, possible, map))
				{
					current->where = possible;
					possible->from = current;
					delete_this_path(map, path);
					return (1);
				}
				possible = possible->where;
			}
			path = path->next;
//		}
	}
	return (0);
}

t_room		*last_room(t_room *start)
{
	t_room	*last;

	last = start;
	while (last->where)
		last = last->where;
	return (last);
}

void 		search_left_paths(t_main *map)
{
	t_path	*path;
	t_room	*current;
	t_room	*start;

	if (map->startway)
	{
		path = map->startway->path;
		while (path)
		{
			if (path->current && !reach_end(path->current, map->end))
			{
				start = path->current;
				current = last_room(start);
				while (current)
				{
					if (path_found(current, map) == 1)
					{
						second_rooms(start, map);
						break;
					}
					current = current->from;
				}
			}
			path = path->next;
		}
	}
}