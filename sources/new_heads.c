#include "lemin.h"

void		change_path_in_structure(t_room *oldstart, t_room *newstart, t_main *map)
{
	t_path	*path;

	path = map->paths;
	while (path)
	{
		if (path->current == oldstart)
		{
			path->current = newstart;
			return;
		}
		path = path->next;
	}
	path = map->startway;
	while (path)
	{
		if (path->current == newstart)
		{
			path->current = oldstart;
			return;
		}
		path = path->next;
	}
}

static int 	new_head_found(t_room *start, t_room *current, t_main *map)
{
	t_path	*path;
	t_room	*possible;
	t_room	*start_of_path;

	path = map->paths;
	while (path)
	{
		possible = path->current;
		start_of_path = possible;
		while (possible)
		{
			if (has_link(current, possible, map) && compare_paths(current->where, possible) > 0)
			{
				possible->from->where = NULL;
				possible->from = current;
				current->where = possible;
				change_path_in_structure(start_of_path, start, map);
				return (1);
			}
			possible = possible->where;
		}
		path = path->next;
	}
	return (0);
}

void 		new_heads(t_main *map)
{
	t_path *path;
	t_room *room;
	t_room *start;

	if (map->startway)
	{
		path = map->startway->path;
		{
			while (path)
			{
				if (reach_end(path->current, map))
					continue;
				start = path->current;
				room = start;
				while (room)
				{
					if (new_head_found(start, room, map))
						break;
					room = room->where;
				}
				path = path->next;
			}
		}
	}
}

