/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_paths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samymone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 16:16:03 by samymone          #+#    #+#             */
/*   Updated: 2020/03/08 16:16:05 by samymone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void		second_rooms(t_room *room, t_main *map)
{
	t_path		*tmp;
	
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
	map->end_connections--;
}

static void		path_is_found(t_room *room, t_main *map)
{
	while (room->from != map->start)
		room = room->from;
	second_rooms(room, map);
}

static void		auxiliary(t_room *first, t_room *second, t_link *link,
							 t_main *map)
{
	if (second->level != 1)
	{
		if (first != map->end)
		{
			if (first->from == NULL && second->where == NULL)
			{
				second->where = first;
				first->from = second;
				link->checked = 2;
			}
		}
		else
		{
			second->where = first;
			link->checked = 2;
		}
		search_previous_room(second, map);
	}
	else
		second_rooms(first, map);
}

t_room			*best_variant4(t_room *current, t_room *variant, t_main *map)
{
	t_link *link;
	t_room *best;

	link = map->all_links_here;
	best = NULL;
	if (variant->level > current->level && variant->inputs > 1)
		return (variant);
	while (link)
	{
		if (ft_strcmp(current->name, link->first_room->name) == 0 ||
			ft_strcmp(current->name, link->second_room->name) == 0)
			printf("STOP\n");
		if (link->first_room == current && link->second_room != variant
		&& !link->second_room->is_dead_end
		&& link->first_room->level < link->second_room->level && link->second_room->inputs > 1
		&& !link->second_room->where)
		{
			best = link->second_room;
			return (link->second_room);
		}
		else if (link->second_room == current && link->first_room != variant
		&& !link->first_room->is_dead_end &&
		link->first_room->level > link->second_room->level && link->first_room->inputs > 1
		&& !link->first_room->where)
		{
			best = link->first_room;
			return (link->first_room);
		}
		link = link->next;
	}
	if (!best)
		return (variant);
}

t_room			*best_variant3(t_room *current, t_room *variant, t_main *map)
{
	t_link		*link;
	t_room		*best;

	link = map->all_links_here;
	best = NULL;
	if (variant->level == current->level && variant->outputs <= 1)
		return (variant);
	while (link)
	{
		if (ft_strcmp(current->name, link->first_room->name) == 0 || ft_strcmp(current->name, link->second_room->name) == 0)
			printf("STOP\n");
		if (link->first_room == current && link->second_room != variant
		&& link->second_room->outputs == 1 && !link->second_room->is_dead_end
		&& link->first_room->level == link->second_room->level
		&& !link->second_room->where)
		{
			best = link->second_room;
			return (link->second_room);
		}
		else if (link->second_room == current && link->first_room != variant
		&& link->first_room->outputs == 1 && !link->first_room->is_dead_end &&
		link->first_room->level == link->second_room->level
		&& !link->first_room->where)
		{
			best = link->first_room;
			return (link->first_room);
		}
		link = link->next;
	}
	if (!best)
		return (best_variant4(current, variant, map));
}


t_room			*best_variant2(t_room *current, t_room *variant, t_main *map)
{
	t_link		*link;
	t_room		*best;

	link = map->all_links_here;
	best = NULL;
	if (variant->level < current->level || variant == map->start)
		return (variant);
	while (link)
	{
		if (ft_strcmp(current->name, link->first_room->name) == 0 || ft_strcmp(current->name, link->second_room->name) == 0)
			printf("STOP\n");
		if (link->first_room == current && link->second_room != variant
		&& !link->second_room->is_dead_end
		&& link->first_room->level > link->second_room->level && link->second_room != map->end
		&& !link->second_room->where)
		{
			best = link->second_room;
			return (link->second_room);
		}
		else if (link->second_room == current && link->first_room != variant
		&& !link->first_room->is_dead_end &&
		link->first_room->level < link->second_room->level && link->first_room != map->end
		&& !link->first_room->where)
		{
			best = link->first_room;
			return (link->first_room);
		}
		link = link->next;
	}
	if (!best)
		return (best_variant3(current, variant, map));
}

/*
 * вернуть variant, если variant -  лучший результат, tmp, если есть результат лучше variant, null, если нет
 * лучшего результата. В том случае, если вернулся null, сделать проверку среди комнат равного уровня
 *
 *
 * переделать данную функцию на 2 этапа: 1) проверка комнат уровнем меньше, 2) проверка комнат того же уровня
 */
t_room			*best_variant(t_room *current, t_room *variant, t_main *map)
{
	t_link		*link;
	t_room		*best;

	best = NULL;
	if ((variant->outputs == 1 && variant->level < current->level)|| variant == map->start)
		return (variant);
	else
	{
		link = map->all_links_here;
		while (link)
		{
			if (ft_strcmp(current->name, link->first_room->name) == 0 || ft_strcmp(current->name, link->second_room->name) == 0)
				printf("STOP\n");
			if (link->first_room == current && link->second_room != variant
			&& link->second_room->outputs == 1 && !link->second_room->is_dead_end
			&& link->first_room->level > link->second_room->level
			&& !link->second_room->where)
			{
				best = link->second_room;
				return (link->second_room);
			}
			else if (link->second_room == current && link->first_room != variant
			&& link->first_room->outputs == 1 && !link->first_room->is_dead_end &&
			link->first_room->level < link->second_room->level && !link->first_room->where)
			{
				best = link->first_room;
				return (link->first_room);
			}
			link = link->next;
		}
	}
	if (!best)
		return (best_variant2(current, variant, map));
}

void			free_path(t_room *current, t_main *map)
{
	t_room		*tmp;
	map->end_connections++;
	while (current && current->where != map->end)
	{
		current->where->from == NULL;
		tmp = current->where;
		current->where = NULL;
		current->from = NULL;
		current = tmp;
	}
	if (current)
		current->from = NULL;
	//start_searching(map->end, map);
}

void			remake_paths(t_room *current, t_main *map)
{
	t_room		*next;
	t_link		*link;

	next = current->where;
	link = map->all_links_here;
	next->from = NULL;

	while (link)
	{
		if (ft_strcmp(next->name, link->first_room->name) == 0 || ft_strcmp(next->name, link->second_room->name) == 0)
			printf("STOP\n");
		if ((link->first_room == current && link->second_room == next)
		|| (link->first_room == next && link->second_room == current))
			link->checked = 1;
		if (link->first_room == next && link->second_room != current && !link->second_room->is_dead_end
		&& link->second_room->level != -1 && link->checked != 2 && !link->second_room->where
		&& best_variant(link->first_room, link->second_room, map) == link->second_room)
		{
			current->where = NULL;
			auxiliary(link->first_room, link->second_room, link, map);
			break ;
		}
		else if (link->second_room == next && link->first_room != current && !link->first_room->is_dead_end
		&& link->first_room->level != -1 && link->checked != 2 && !link->first_room->where
		&& best_variant(link->second_room, link->first_room, map) == link->first_room)
		{
			current->where = NULL;

			auxiliary(link->second_room, link->first_room, link, map);
			break ;
		}
		link = link->next;
	}
	if (!current->from)
		free_path(current, map);
}

void			search_previous_room(t_room *current, t_main *map)
{
	t_link		*link;

	link = map->all_links_here;
	while (current->level == 1 ||
	current->where == NULL || current->from == NULL)
	{
		if (ft_strcmp(current->name, link->first_room->name) == 0 || ft_strcmp(current->name, link->second_room->name) == 0)
			printf("STOP\n");
		if (link->first_room == current && !link->second_room->is_dead_end &&
		/*link->first_room->level >= link->second_room->level *//*|| (link->first_room->level == link->second_room->level
		&& link->second_room->outputs == 1))&&*/
		link->second_room->level != -1 && link->checked != 2 && !link->second_room->where
		&& best_variant(link->first_room, link->second_room,  map) == link->second_room)
		{
			auxiliary(link->first_room, link->second_room, link, map);
			break ;
		}
		else if (link->second_room == current && !link->first_room->is_dead_end /*&&
				link->first_room->level <= link->second_room->level*/ /*|| (link->first_room->level == link->second_room->level
				&& link->first_room->outputs == 1))*/ &&
		link->first_room->level != -1 && link->checked != 2 && !link->first_room->where
		&& best_variant(link->second_room, link->first_room, map) == link->first_room)
		{
			auxiliary(link->second_room, link->first_room, link, map);
			break ;
		}

		if (link->next)
			link = link->next;
		else if (!current->from)
		{
			remake_paths(current, map);
			break;
		}
		else
			break ;
	}
	start_searching(map->end, map);
}

void			start_searching(t_room *room, t_main *map)
{
	t_link		*link;
	t_room		*tmp;

	tmp = NULL;
	link = map->all_links_here;
	while (link)
	{
		if (link->first_room == map->end && !link->second_room->where && link->second_room->level)
		{
			if (!tmp || tmp->level > link->second_room->level)
				tmp = link->second_room;
		}
		else if (link->second_room == map->end && !link->first_room->where && link->first_room->level)
		{
			if (!tmp || tmp->level > link->first_room->level)
				tmp = link->first_room;
		}
		link = link->next;
	}
	if (tmp)
	{
		map->end_connections--;
		tmp->where = map->end;
		search_previous_room(tmp, map);
	}
}
