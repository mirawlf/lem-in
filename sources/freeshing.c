/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeshing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 16:53:51 by student           #+#    #+#             */
/*   Updated: 2020/05/20 16:53:54 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
 * потом добавить чистку комнат и муравьев, тк если все збс при считывании, то
 * нужно будет все фришить в конце программы
 */

void 		free_rooms(t_room *room, t_room *start, t_room *end)
{
	t_room	*tmp;
	t_room	*next;

	tmp = room;
	while (tmp)
	{
		if (tmp != start && tmp != end)
		{
			free(tmp->where);
			free(tmp->from);
		}
		free(tmp->name);
		free(tmp->ant); //надо ли? или только для комнаты end???
		next = tmp->next;
		free(tmp->next);
		free(tmp);
		tmp = next;
	}
}

void 		free_links(t_link *link)
{
	t_link	*tmp;
	t_link	*next;

	tmp = link;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->next);
		free(tmp);
		tmp = next;
	}
}

void 		free_paths(t_path *path)
{
	t_path	*tmp;
	t_path	*next;

	tmp = path;
	while (tmp)
	{

		next = tmp->next;
		free(tmp->next);
		free(tmp);
		if (tmp->next)
			tmp = next;
		else if(tmp->next->next)
			tmp = tmp->next->next;
	}
}

void 		free_ants(t_ant *ant)
{
	t_ant	*tmp;
	t_ant	*next;

	tmp = ant;
	while (tmp)
	{
		tmp->num = 0;
		next = tmp->next;
		//free(tmp->prev);//есть ли prev??? // Teper' est'
		free(tmp->next);
		free(tmp);
		tmp = next;
	}
}


void		freeshing(t_main *map)
{
	free_rooms(map->all_rooms_here, map->start, map->end);
	free(map->all_rooms_here);
	map->all_rooms_here = NULL;
	free_links(map->all_links_here);
	free(map->all_links_here);
	map->all_links_here = NULL;
	free(map->start);
	free(map->end);
	free(map->line);
	free(map->courier);
	free_paths(map->paths);
	free(map->paths);
	map->paths = NULL;
	free_paths(map->endway->path);
	free(map->endway);
	map->endway = NULL;
	free_paths(map->startway->path);
	free(map->startway);
	map->startway = NULL;
	free_ants(map->first_ant);
	free(map->first_ant);
	map->first_ant = NULL;
	free(map->path_array);
	map->path_array = NULL;
	free(map);
}

/*
 *
 *
 * old
 */

//void		free_map(t_main *map)
//{
//	if (map)
//		free(map);
//}
//
//void		free_rooms(t_room *room)
//{
//	if (!room)
//		return ;
//	while(room->next)
//		free_rooms(room->next);////////а room?
//	if (room->name)
//		free(room->name);
//	free(room);
//}
//
///*/void		free_ant(int i, t_ant *ant)
//{
//	t_ant	*curr;
//
//	while (i-- > 0)
//	{
//		if (ant->next)
//			curr = ant->next;
//		ant->num = 0;///////зачем
//	//	free(ant->prev);
//		free(ant->next);
//		free(ant->curr_room);
//		ant = curr;
//	}
//	free(ant);
//}*/
//
//void		free_split(char **split)
//{
//	int		i;
//
//	i = 0;
//	if (split)
//	{
//		while(split[i])
//		{
//			ft_strdel(&split[i]);
//			i++;
//		}
//		free(split);
//	}
//	split = NULL;
//}

void			free_path(t_room *current, t_main *map)
{
	t_room		*tmp;

	while (current && current->where != map->end)
	{
		if (current)
		{
			if (current->where)
				current->where->from = NULL;
		}
		tmp = current->where;
		current->where = NULL;
		current->from = NULL;
		current = tmp;
	}
	if (current)
		current->from = NULL;
}