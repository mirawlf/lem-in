#include "lemin.h"

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
	path = map->endway->path;
	while (path)
	{
		possible = path->current;
		while (possible)
		{
			if (has_link(current, possible, map) == 1)
			{
				current->where = possible;
				possible->from = current;
				return (1);
			}
			possible = possible->where;
		}
		path = path->next;
	}
	return (0);
}

void 		search_left_paths(t_main *map)
{
	t_path	*path;
	t_room	*current;
	t_room	*tmp;

	path = map->startway->path;
	while (path)
	{
		current = path->current;
		while (current)
		{
			if (path_found(current, map) == 1)
			{
				tmp = current;
				while (tmp->from)
					tmp = tmp->from;
				current = tmp;
				second_rooms(current, map);
				break;
			}
			current = current->where;
		}
		path = path->next;
	}
}