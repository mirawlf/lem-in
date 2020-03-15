/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 21:16:14 by cyuriko           #+#    #+#             */
/*   Updated: 2020/02/09 15:34:30 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		print_step(int ant_num, char *room_name, t_main *main)
{
	ft_putchar('L');
	ft_putnbr((main->original_ants + 1 - ant_num));
	ft_putchar('-');
	ft_putstr(room_name);
	ft_putchar(' ');
}

int			print_line(int ret, char *line)
{
	ft_putstr_fd(line, 1);
	ft_putchar('\n');
	return (ret);
}
