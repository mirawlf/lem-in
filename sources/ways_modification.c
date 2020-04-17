#include "lemin.h"

int 		check_length(t_room *current, t_room *prev)
{
	t_room	*tmp;
	int 	old;
	int 	new;

	old = 0;
	new = 0;
	tmp = current;
	while (tmp)
	{
		new++;
		tmp = tmp->from;
	}
	tmp = prev;
	while (tmp)
	{
		old++;
		tmp = tmp->from;
	}
	return (old - new);
}
/*old thing without path adding
 *
 * */
void		exchange(t_room *current, t_room *variant, t_main *map)
{
	t_room	*old;
	t_room	*new;
	t_path	*tmp;
	t_path	*start;

	old = variant->from;
	old->where = NULL;
	new = current;
	variant->from = current;
	current->where = variant;
	while (old->from)
		old = old->from;
	while (new->from)
		new = new->from;
	tmp = map->paths;
	while (tmp->current != old)
		tmp = tmp->next;
	//if (tmp->current == old)
	tmp->current = new;
	//else
	//{
	//	if (!(tmp->next = (t_path*)ft_memalloc(sizeof(t_path))))
	//		ft_error("malloc failed\n");
	//	tmp->next->current = new;
	//}
	start = map->startway->path;
	while (start->next->current != new)
		start = start->next;
	start->next->current = old;
}
/*void		exchange(t_room *current, t_room *variant, t_main *map)
{
	t_room	*old;
	t_room	*new;
	t_path	*tmp;
	t_path	*start;

	old = variant->from;
	old->where = NULL;
	new = current;
	variant->from = current;
	current->where = variant;
	while (old->from)
		old = old->from;
	while (new->from)
		new = new->from;
	tmp = map->paths;
	while (tmp && tmp->current != old)
		tmp = tmp->next;
	if (tmp && tmp->current == old)
		tmp->current = new;
	else
	{
		tmp = map->paths;
		while (tmp->next)
			tmp = tmp->next;
		if (!(tmp->next = (t_path*)ft_memalloc(sizeof(t_path))))
			ft_error("malloc failed\n");
		tmp->next->current = new;
	}
	start = map->startway->path;
	while (start->next->current != new)
		start = start->next;
	start->next->current = old;
}*/
/*
 * delete this?
 */
static int is_written_in_history2(t_room *check, t_path *paths)
{
	t_path *start = paths;
	t_room *finder;

	finder = check;
	while (finder->from)
		finder = finder->from;
	while (start)
	{
		if (start->current == finder)
			return (1);
		start = start->next;
	}
	return (0);
}
static int is_written_in_history(t_room *check, t_path *paths)
{
	t_path *start;
	t_room *checker;

	if (!check || !paths)
		return (0);
	start = paths;
	while (start)
	{
		checker = start->current;
		while (checker)
		{
			if (checker == check)
				return (1);
			checker = checker->next;
		}
		start = start->next;
	}
	return (0);
}

int 		reach_end(t_room *room,  t_room *end)
{
	t_room	*tmp;

	tmp = room;
	while (tmp)
	{
		if (tmp->where == end)
			return (1);
		tmp = tmp->where;
	}
	return (0);
}

void 		try_to_change_tails(t_room *current, t_main *map)
{
	t_link	*link;

	link = map->all_links_here;
	while (link)
	{
		if (link->first_room == current && !link->second_room->is_dead_end
		&& check_length(current, link->second_room->from) > 0)
		{
			if (reach_end(link->second_room, map->end) == 1 /*ok careful here*//*fuck it&& is_written_in_history2(link->second_room, map->paths)*/)
				exchange(current, link->second_room, map);
			else
			{
				link->second_room->from->where = NULL;
				link->second_room->from = link->first_room;
				link->first_room->where = link->second_room;
				if (!link->second_room->where)
					search_next_room(link->second_room, map);
			}
			break;
		}
		else if (link->second_room == current && !link->first_room->is_dead_end
		&& check_length(current, link->first_room->from) > 0)
		{
			if (reach_end(link->first_room, map->end) == 1)
				exchange(current, link->first_room, map);
			else
			{
				link->first_room->from->where = NULL;
				link->first_room->from = link->second_room;
				link->second_room->where = link->first_room;
				if (!link->first_room->where)
					search_next_room(link->first_room, map);
			}
			break;
		}
		link = link->next;
	}
}
