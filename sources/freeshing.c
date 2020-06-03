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

void			free_rooms(t_room *room)
{
	t_room		*tmp;

	tmp = room;
	if (tmp)
	{
		free(tmp->name);
		free_rooms(tmp->next);
		free(tmp);
	}
}

void			free_links(t_link *link)
{
	t_link		*tmp;
	t_link		*next;

	while (tmp)
	{
		if (tmp->next)
			next = tmp->next;
		free(tmp);
		tmp = next;
	}
}

void			free_paths(t_path *path)
{
	t_path		*tmp;

	tmp = path;
	if (tmp)
	{
		free_paths(tmp->next);
		free(tmp);
	}
}

void			free_ants(t_ant *ant)
{
	t_ant		*tmp;
	t_ant		*next;

	tmp = ant;
	while (tmp)
	{
		tmp->num = 0;
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
}

void			free_mapfile(t_mapfile *mapfile)
{
	t_mapfile	*tmp;
	t_mapfile	*next;

	tmp = mapfile;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->text);
		free(tmp);
		tmp = next;
	}
}
