/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 21:16:14 by cyuriko           #+#    #+#             */
/*   Updated: 2020/01/26 18:56:31 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void 	print_step(int ant_num, char *room_name)
{
	ft_putchar('L');
	ft_putnbr(ant_num);
	ft_putchar('-');
	ft_putstr(room_name);
	ft_putchar(' ');
}

int 	print_line(int ret, char *line)/////////это мне при правильном вводе понадобится
{
	ft_putstr_fd(line, 1);
	ft_putchar('\n');
	return (ret);
}