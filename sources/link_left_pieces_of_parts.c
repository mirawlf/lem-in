//#include "lemin.h"
//
//void 		appoint_flag(t_main *map)
//{
//	t_path	*path;
//	t_room	*room;
//
//	path = map->paths;
//	while (path)
//	{
//		room = path->current;
//		while (room)
//		{
//			room->is_part_of_path = 1;
//			room = room->where;
//		}
//		path = path->next;
//	}
//	path = map->startway;
//	while (path)
//	{
//		room = path->current;
//		while (room)
//		{
//			room->is_part_of_path = 2;
//			room = room->where;
//		}
//		path = path->next;
//	}
//	path = map->endway;
//	{
//		while (path)
//		{
//			room = path->current;
//			while (room)
//			{
//				room->is_part_of_path = 3;
//				room = room->where;
//			}
//			path = path->next;
//		}
//	}
//}
//
//t_room		*last_room(t_room *first)
//{
//	while (first->where)
//		first = first->where;
//	return (first);
//}
//
//int 		tail_is_found(t_room *current, t_main *map)
//{
//	t_path	*path;
//
//	path = map->endway->path;
//	while (path)
//	{
//		if (has_link(current, path->current, map))
//		{
//			current->where = path->current;
//			path->current->from = current;
//			return (1);
//		}
//		path = path->next;
//	}
//	return (0);
//}
//
//void 		search_gap(t_room *first, t_room *last, t_main *map)
//{
//	t_link	*link;
//
//	link = map->all_links_here;
//	while (link)
//	{
//		if (link->first_room == last && link->second_room != last->from &&
//		!link->second_room->is_dead_end && best_room(link->first_room, link->second_room, map)
//		== link->second_room)
//		{
//			link->first_room->where = link->second_room;
//			link->second_room->from = link->first_room;
//			link->checked = 2;
//
//		}
//		link = link->next;
//	}
//	if (!last->where)
//		return;
//}
//
//void 		link_left_pieces(t_main *map)
//{
//	t_path	*start;
//	t_room	*first;
//	t_room	*last;
//
//	////найти последнюю комнату стартвея, запомнив первую, найти комнаты, не являющиеся частью пути,
//	////проверить линк, после проверить линк на первые комнаты эндвея (и последующие???)
//	////если всё соединилось, добавить путь
//
//	appoint_flag(map);
//	start = map->startway->path;
//	while (start)
//	{
//		first = start->current;
//		last = last_room(first);
//		//if (last != map->end)
//		//	search_gap(first, last, map);
//		start = start->next;
//	}
//}