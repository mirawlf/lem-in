/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redrum.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 12:45:41 by cyuriko           #+#    #+#             */
/*   Updated: 2019/12/21 19:41:35 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int read_me_a_room_line(t_main *main, int fd)
{
	char *kostyl_for_connection;

	if (!(get_next_line(fd, &main->line)) || !(line_exists(main->line)))
		return (-1); ///в строке опять хуйня
	if (!(check_comment(main->line)))
		return (2);////это ебучий коммент
	if (check_command(main->line) == 1)
		return (3);////это строка ##start
	else if (check_command(main->line) == 2)
		return (4);/////это строка ##end
	if ((kostyl_for_connection = check_connection(main->line)))
	{
		free_split(kostyl_for_connection);/////////ебаное уродство исправь блядь илюха не позорься
		return (5);/////это коннекшн
	}

	return (0);
}

static t_room	*find_start(t_main *main, char *line, t_room *current)
{
	t_room	*start;

	if (!(start = create_room(line)))
		return (NULL);
	//start->is_part_of_path = 1;
	main->start = start;
	if (current)
		current->next = start;
	return (start);
}

static t_room	*find_end(t_main *main, t_room *current, char *line)
{
	t_room	*end;

	if (!(end = create_room(line)))
		return (NULL);
	main->end = end;
	current->next = end;
	return (end);
}

static t_room	*find_middle(t_room *current, char *line)
{
	t_room	*incoming;

	if (!(incoming = create_room(line)))
		return (NULL);
	if (current)
		current->next = incoming;
	return (incoming);
}

t_room 	*read_rooms(t_main *main, int fd)
{
	t_room	*start;
	t_room	*current;
	t_room	*prev;
	int 	check;
	int finished;

	start = NULL;
	current = NULL;
	prev = NULL;
	finished = 1;
	while (finished != 0)
	{
		prev = current;
		check = read_me_a_room_line(main, fd);
		if (check == -1)
			free_rooms(start);
		else if (check == 2)
			continue;
		else if (check == 5)
			finished = 0;
		else if (!check)
		{
			if (finished == 1)
				current = find_middle(prev, main->line);
			else if (finished == 2)
				current = find_start(main, main->line, prev);
			else if (finished == 3)
				current = find_end(main, prev, main->line);
			if (!start)
				start = current;
			finished = 1;
		}
		else if (check == 3)
			finished = 2;
		else if (check == 4)
			finished = 3;
		if (main->line && finished)
			ft_strdel(&main->line);
	}
	return (start);
}