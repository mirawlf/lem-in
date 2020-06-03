/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 20:28:06 by student           #+#    #+#             */
/*   Updated: 2020/06/03 20:28:11 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void			print_step(int ant_num, char *room_name, t_main *main)
{
	ft_putchar('L');
	ft_putnbr((main->original_ants + 1 - ant_num));
	ft_putchar('-');
	ft_putstr(room_name);
	ft_putchar(' ');
}

void			print_map(t_mapfile *text)
{
	t_mapfile	*line;

	line = text;
	while (line)
	{
		ft_putstr(line->text);
		ft_putstr("\n");
		line = line->next;
	}
	ft_putstr("\n");
}
