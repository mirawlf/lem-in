/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easy_rider.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 17:30:37 by cyuriko           #+#    #+#             */
/*   Updated: 2019/12/18 19:22:15 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
/**
 *
 * @param line = проверяемая строка
 * @return 0 на валидной комнате, -1 на невалидной
 */
int 	check_room(char *line)
{
	char **split;
	int counter;
	int i;

	counter = 0;
	if (!(split = ft_strsplit(line, ' ')))
		return (-1);
	while (split[counter])
		counter++;
	if (counter != 2)
		return (-1);
	counter = 1;
	while(counter < 3)
	{
		i = 0;
		while(split[counter][i])/////////тэк бля вот эта херня течет не забыть бы ее поправить
		{
			if (!(ft_isdigit(split[counter][i])))
				return (-1);
			i++;
		}
		counter++;
	}
	return (0);
}
/**
 *
 * @param message - текст ошибки
 * потом делается экзит
 */
void		bad_shit_happened(char *message)
{
	ft_putstr_fd(message, 2);
	exit(777);
}