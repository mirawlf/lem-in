/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   soulmates.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 19:47:21 by cyuriko           #+#    #+#             */
/*   Updated: 2019/12/22 20:55:09 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int read_me_a_room_line(t_main *main, int fd)
{
	char **split;
	int command;
	if (!(get_next_line(fd, &main->line)))
		return (0); //ДОЧИТАЛИ
	if (!(line_exists(main->line)))
		return (-1);///в строке опять хуйня
	command = check_command(main->line);
	if (!(check_comment(main->line)) || command == 3)
		return (2);////это ебучий коммент
	if (command < 3 && command > 0)
		return (-1);////это команда ебучая
	if (split = check_connection(main->line))
	{
		free_split(split);//////уродство конечно пиздос
		return (5);/////это коннекшн
	}
	return (-1);
}

static t_link	*create_new_link(t_link *prev, t_main *main)
{
	t_link	*link;

	if (!(link = ft_memalloc(sizeof(t_link))))
		return (NULL);
	if (prev)
		prev->next = link;
	return (link);
}

static t_link 	*find_and_connect(t_link *link, t_room *rooms, char **split)
{
	t_room	*start;

	start = rooms;
	while (start)
	{
		if (ft_strequ(split[0], start->name) && !(link->first_room))
			link->first_room = start;
		else if (ft_strequ(split[1], start->name) && !(link->second_room))
			link->second_room = start;
		else if (link->first_room && link->second_room)
			break;
		start = start->next;
	}
	if (!(link->first_room) || !(link->second_room))
		ft_error("ERROR: INVALID ROOM NAME IN A LINK");
	return (link);
}

static t_link	*initial_connection(t_main *main)
{
	t_link	*start;
	char 	**split;

	split = check_connection(main->line);
	start = create_new_link(NULL, main);
	start = find_and_connect(start, main->all_rooms_here, split);
	return (start);
}

t_link	*get_me_links(t_main *main, int fd, t_room *room)
{
	t_link	*start;
	t_link	*current;
	int 	check;
	char	**split;

	check = 1;
	start = NULL;
	current = NULL;
	current = initial_connection(main);
	start = current;
	while (check)
	{
		check = read_me_a_room_line(main, fd);///////////тут лайн течет как мразь
		if (check == -1)
			ft_error("ERROR: INVALID ROOM");
		else if (!check)
			break;
		else if (check == 2)
			continue;
		else if (check == 5)
		{
			split = check_connection(main->line);
			current = create_new_link(current, main);
			current = find_and_connect(current, room, split);
			free_split(split);
		}
	}
	return (start);
}