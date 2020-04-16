#include "lemin.h"

static int	found_shorter_path(t_room *current, t_main *map)
{
	t_path	*path;
	t_room	*possible;
	t_room	*tmp;

	if (map->endway)
	{
		path = map->endway->path;
		while (path)
		{
			possible = path->current;
			while (possible)
			{
				if (has_link(current, possible, map) && reach_end(possible, map->end)
				&& compare_paths(current->where, possible) > 0)
				{
					tmp = current->where;
					current->where = possible;
					possible->from = current;
					if (tmp && tmp->from)
						tmp->from = NULL;
					return (1);
				}
				possible = possible->where;
			}
			path = path->next;
		}
	}
	return (0);
}

void 		new_tails(t_main *map)
{
	t_path	*path;
	t_room	*current;

	if (map->paths)
	{
		path = map->paths;
		while (path)
		{
			current = path->current;
			while (current->where != map->end)
			{
				if (found_shorter_path(current, map) == 1)
					break;
				current = current->where;
			}
			path = path->next;
		}
	}
}