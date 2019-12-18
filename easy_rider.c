/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easy_rider.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 17:30:37 by cyuriko           #+#    #+#             */
/*   Updated: 2019/12/18 20:09:35 by cyuriko          ###   ########.fr       */
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

static void		free_split(char **split)
{
	int i;

	i = 0;
	if (split)
	{
		while(split[i])
		{
			free(split[i])
			i++;
		}
		free(split);
	}
}
/**
 *
 * @param line строка очередная
 * @return расспличенную строку с названием и координатами, NULL при невалидном вводе
 */
char 	**check_room(char *line)
{
	char **split;
	int counter;

	counter = 0;
	if (!(split = ft_strsplit(line, ' ')) || count_room_entries(split) != 2)
	{
		free_split(split);
		return (NULL);
	}
	counter = 1;
	while(counter < 3)
	{
		i = 0;
		while(split[counter][i])/////////тэк бля вот эта херня течет не забыть бы ее поправить
		{
			if (!(ft_isdigit(split[counter][i])))
			{
				free(split);
				return (NULL);
			}
			i++;
		}
		counter++;
	}
	return (split);
}

int 	create_room(char *line, )
{
	char **room_with_coords;


}