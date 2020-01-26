/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easy_rider.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 17:30:37 by cyuriko           #+#    #+#             */
/*   Updated: 2020/01/26 11:15:25 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
/**
 *
 * @param line = проверяемая строка
 * @return 0 на валидной комнате, -1 на невалидной
 */

static int 	count_room_entries(char **split)
{
	int	i;

	i = 0;
	while(split[i])
		i++;
	return (i);
}
/**
 *
 * @param line строка очередная
 * @return расспличенную строку с названием и координатами, NULL при невалидном вводе
 */
static char 	**check_room(char *line)
{
	char **split;
	int counter;
	int i;

	counter = 0;
	if (!(split = ft_strsplit(line, ' ')) || count_room_entries(split) != 3)
	{
		free_split(split);
		return (NULL);
	}
	counter = 1;
	while(counter < 3)
	{
		i = 0;
		while(split[counter][i])
		{
			if (!(ft_isdigit(split[counter][i])))
			{
				free_split(split);
				return (NULL);
			}
			i++;
		}
		counter++;
	}
	return (split);
}

t_room		*create_room(char *line)
{
	char **split;
	t_room	*room;

	if (!(split = check_room(line)))
		return (NULL);
	if (!(room = ft_memalloc(sizeof(t_room))))
		return (NULL);
	room->name = ft_strdup(split[0]);
	room->x = ft_atoi(split[1]);
	room->y = ft_atoi(split[2]);
	free_split(split);
	return (room);
}

