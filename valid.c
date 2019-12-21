/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 17:11:52 by cyuriko           #+#    #+#             */
/*   Updated: 2019/12/21 18:02:22 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
/**
 *
 * @param line = проверяемая строка, не NULL!
 * @return 0 если это коммент, 1 - если строка есть и это не коммент
 */
int 	check_comment(char *line)
{
	if (ft_strlen(line) < 2)
		return (1);
	if (line[0] == '#' && line[1] != '#')
		return (0);
	return (1);
}
/**
 *
 * @param line  = проверяемая строка
 * @return 1 если строка существует, 0 если нет
 */
int 	line_exists(char *line)
{
	if (!line)
		return (0);
	if (!ft_strlen(line))
		return (0);
	return (1);
}

/**
 *
 * @param line  = проверяемая строка
 * @return 0 если это не команда вовсе, 1 если старт, 2 если энд, 3 если это странный коммент который надо игнорить
 */
int 	check_command(char *line)
{
	if (ft_strlen(line) > 3)
	{
		if (ft_strequ(line, "##start"))
			return (1);
		if (ft_strequ(line, "##end"))
			return (2);
		if (line[0] == '#' && line[1] == '#' && line[2] != '#')
			return (3);
	}
	return (0);
}

/**
 *
 * @param line = проверяемая строка
 * @param map = запишет в map->ants количество муравьев
 * @return 0 при успехе, -1 - кажется, что-то пошло по пизде
 */
int 	check_and_write_ants(char *line, t_main *map)
{
	int		i;

	if (!line_exists(line))
		return (-1);
	i = 0;
	while (line[i] && ft_isdigit(line[i]))
		i++;
	if (ft_strlen(line) != i)
		return (-1);
	map->ants = ft_atoi(line);
	if (map->ants < 1)
		return (-1);
	return (0);
}

int 	check_connection(char *line)
{
	char **split;
	int i;

	i = 0;
	split = ft_strsplit(line, '-');
	if (split)
	{
		while(split[i])
			i++;
		free_split(split);
		if (i == 2)
			return (0);
	}
	return (-1);
}