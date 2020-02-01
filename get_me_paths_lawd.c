#include "lemin.h"

static	void	fill_path(t_path *path, t_room *room)
{
	if (path && room)
		path->current = room;
}


t_room	*list_posiible_paths(t_link *link, t_main *main, t_path *path)
{

	if (link->first_room == main->start || link->second_room == main->start)
	{
		if (!path)
			path = (t_path*)ft_memalloc(sizeof(t_path));
		else
		{
			while (path->next)
				path = path->next;
			path->next = (t_path *) ft_memalloc(sizeof(t_path));
			path = path->next;
		}
			if (link->first_room == main->start)
				fill_path(path, link->second_room);
			else
				fill_path(path, link->first_room);
	return ()
	}


}