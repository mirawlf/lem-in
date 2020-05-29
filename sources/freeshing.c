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

void		free_rooms(t_room *room)
{
	t_room	*tmp;

	tmp = room;
	if (tmp)
	{
		free(tmp->name);
		free_rooms(tmp->next);
		//tmp->where = NULL;
		//tmp->from = NULL;
		free(tmp);
	}
}

void		free_links(t_link *link)
{
	t_link	*tmp;
	t_link	*next;

	while (tmp)
	{
		if (tmp->next)
			next = tmp->next;
		free(tmp);
		tmp = next;
	}
}

void		free_paths(t_path *path)
{
	t_path	*tmp;

	tmp = path;
	if (tmp)
	{
		free_paths(tmp->next);
		free(tmp);
	}
}

void		free_ants(t_ant *ant)
{
	t_ant	*tmp;
	t_ant	*next;

	tmp = ant;
	while (tmp)
	{
		tmp->num = 0;
		next = tmp->next;
		//free(tmp->prev);//есть ли prev??? // Teper' est'
		free(tmp);
		tmp = next;
	}
}

void 		free_mapfile(t_mapfile *mapfile)
{
	t_mapfile	*tmp;
	t_mapfile 	*next;

	tmp = mapfile;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->text);
		free(tmp);
		tmp = next;
	}
}

void		freeshing(t_main *map)
{
	free_rooms(map->all_rooms_here);
	map->all_rooms_here = NULL;
	//free_links(map->all_links_here);
	map->all_links_here = NULL;
	free(map->line);
	free(map->courier);
	free_paths(map->paths);
	//free(map->paths);
	map->paths = NULL;
	if (map->endway)
	{
		free_paths(map->endway->path);
		//free(map->endway);
		map->endway = NULL;
	}
	if (map->startway)
	{
		free_paths(map->startway->path);
		//free(map->startway);
		map->startway = NULL;
	}
	free_ants(map->first_ant);
	free(map->first_ant);
	map->first_ant = NULL;
	free(map->path_array);
	map->path_array = NULL;
	free_mapfile(map->mapfile);
//	free(map->mapfile);
	free(map);
}

void		free_path(t_room *current, t_main *map)
{
	t_room	*tmp;

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