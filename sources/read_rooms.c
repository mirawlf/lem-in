/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_rooms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 17:26:18 by student           #+#    #+#             */
/*   Updated: 2020/05/20 17:26:21 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int					valid_coords(t_room *room, t_room *list)
{
	t_room			*start;

	start = list;
	while (start)
	{
		if (start->x == room->x)
		{
			if (start->y == room->y)
				return (0);
		}
		start = start->next;
	}
	return (1);
}

static t_room		*make_room(t_room *room, char *line, t_main *data)
{
	t_room			*result;
	char			**room_data;

	if (!(result = (t_room*)ft_memalloc(sizeof(t_room))))
		return (NULL);
	if (room)
		room->next = result;
	if (!(room_data = ft_strsplit(line, ' ')))
		return (0);
	result->name = ft_strdup(room_data[0]);
	result->x = ft_atoi(room_data[1]);
	result->y = ft_atoi(room_data[2]);
	del_str_arr(room_data);
	if (!data->all_rooms_here)
		data->all_rooms_here = result;
	ft_strdel(&line);
	return (result);
}

static int			start_end_check(char *line, t_room **rooms, t_main *data)
{
	int				flag;

	flag = 0;
	flag = flag_value(flag, line);
	ft_strdel(&line);
	if (flag != 1 && flag != 2)
		return (1);
	if ((get_next_line(0, &line) < 1) || !(is_room(line)))
		return (del_line_and_return(line, 1));
	if (flag == 1 && !data->start)
	{
		if (!(*rooms = make_room(*rooms, line, data)))
			return (del_line_and_return(line, 0));
		data->start = *rooms;
		data->start->is_part_of_path = 1;
		return (1);
	}
	else if (flag == 2 && !data->end)
	{
		if (!(*rooms = make_room(*rooms, line, data)))
			return (del_line_and_return(line, 0));
		data->end = *rooms;
		return (1);
	}
	return (del_line_and_return(line, 0));
}

static int			reached_links(t_main *data, char *line)
{
	data->courier = line;
	return (1);
}

int					read_rooms(t_main *data)
{
	char			*line;
	t_room			*rooms;
	int				ret;

	rooms = NULL;
	while ((ret = get_next_line(0, &line)) > 0)
	{
		new_line_for_mapfile(data->mapfile, line);
		if (is_comment(line) && start_end_check(line, &rooms, data))
			continue;
		if (is_room(line))
		{
			rooms = make_room(rooms, line, data);
			if (valid_coords(rooms, data->all_rooms_here))
				return (0);
			continue;
		}
		if (is_link(line))
			return (reached_links(data, line));
		else
			return (0);
	}
	return ((ret > 0) ? del_line_and_return(line, 1) : 0);
}
