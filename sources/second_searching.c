/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_searching.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samymone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 19:20:54 by samymone          #+#    #+#             */
/*   Updated: 2020/03/15 19:21:00 by samymone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void             auxiliary2(t_room *from, t_room *where, t_link *link, t_main *map)
{
    from->where = where;
    where->from = from;
    link->checked = 2;
    search_next_room(where, map);
}

void             search_next_room(t_room *current, t_main *map)
{
    t_link      *link;

    link = map->all_links_here;
    while (link)
    {
        if (link->first_room == current && !link->second_room->from && !link->second_room->where
        && !link->second_room->is_dead_end && link->checked != 2 &&
        best_room(link->first_room, link->second_room, map)
        == link->second_room)
        {
       		auxiliary2(link->first_room, link->second_room, link, map);
			break;
        }
        else if (link->second_room == current && !link->first_room->from
        && !link->first_room->where && !link->first_room->is_dead_end && link->checked != 2 &&
        best_room(link->second_room, link->first_room, map)
        == link->first_room)
        {
            auxiliary2(link->second_room, link->first_room, link, map);
            break;
        }
        link = link->next;
    }
    if (!current->where)
        try_to_change_tails(current, map);
}

void             another_possible_ways(t_room *room, t_main *map)
{
    t_path *tmp;

    if (!map->startway)
    {
        if (!(map->startway = (t_fromstart*)ft_memalloc(sizeof(t_fromstart)))
        || !(map->startway->path = (t_path*)ft_memalloc(sizeof(t_path))))
            ft_error("malloc failed\n");
        map->startway->path->current = room;
    }
    else
    {
        tmp = map->startway->path;
        while (tmp->next)
            tmp = tmp->next;
        if (!(tmp->next = (t_path*)ft_memalloc(sizeof(t_path))))
			return ;
        tmp = tmp->next;
        tmp->current = room;
    }
    search_next_room(room, map);
}

void        search_intersections(t_main *map)
{
    t_link  *link;

    link = map->all_links_here;
    while (link)
    {
        if (link->first_room == map->start && !link->second_room->where)
            another_possible_ways(link->second_room, map);
        else if (link->second_room == map->start && !link->first_room->where)
            another_possible_ways(link->first_room, map);
        link = link->next;
    }
    search_left_paths(map);
    new_tails(map);
    new_heads(map);
    search_left_paths(map);
}
