/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_links.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 17:08:07 by student           #+#    #+#             */
/*   Updated: 2020/05/20 17:08:10 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int				duplicate_links(t_link *link, t_main *data)
{
	t_link		*start;

	start = data->all_links_here;
	while (start != link && start)
	{
		if ((start->first_room == link->first_room &&
		start->second_room == link->second_room) ||
		(start->first_room == link->second_room &&
		start->second_room == link->first_room))
			return (1);
		start = start->next;
	}
	return (0);
}

static t_room	*find_room(t_main *data, char *name)
{
	t_room		*room;

	room = data->all_rooms_here;
	while (room)
	{
		if (ft_strequ(room->name, name))
			return (room);
		room = room->next;
	}
	return (NULL);
}

static t_link	*make_link(char *line, t_link *link, t_main *data)
{
	t_link		*result;
	char		**split;

	if (!(result = (t_link*)ft_memalloc(sizeof(t_link))))
	{
		ft_strdel(&line);
		return (NULL);
	}
	link->next = result;
	if (!(split = ft_strsplit(line, '-')))
	{
		ft_strdel(&line);
		return (NULL);
	}
	ft_strdel(&line);
	result->first_room = find_room(data, split[0]);
	result->second_room = find_room(data, split[1]);
	del_str_arr(split);
	if (!result->first_room || !result->second_room
	|| duplicate_links(result, data))
		return (NULL);
	return (result);
}

static t_link	*initital_link(t_main *data)
{
	t_link		*result;
	char		**split;

	split = NULL;
	if (!(result = (t_link*)ft_memalloc(sizeof(t_link))))
		return (NULL);
	data->all_links_here = result;
	if (!(split = ft_strsplit(data->courier, '-')))
		return (NULL);
	ft_strdel(&data->courier);
	result->first_room = find_room(data, split[0]);
	result->second_room = find_room(data, split[1]);
	del_str_arr(split);
	if (!result->first_room || !result->second_room)
		return (NULL);
	return (result);
}

int				read_links(t_main *data)
{
	t_link		*link;
	char		*line;
	int			check;

	if (!(link = initital_link(data)))
		return (0);
	while (get_next_line(0, &line) > 0)
	{
		new_line_for_mapfile(data->mapfile, line);
		if (is_comment(line))
		{
			check = is_command(line);
			ft_strdel(&line);
			if (!check)
				continue;
			break ;
		}
		if (is_link(line) && (link = make_link(line, link, data)))
			continue;
		else
			return (0);
	}
	return (1);
}
