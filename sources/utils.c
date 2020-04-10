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

int			ft_error(const char *error)
{
	ft_putendl_fd(error, 2);
	exit(-1);
}

int			del_line_and_return(char *line, int ret)
{
	free(line);
	line = NULL;
	return (ret);
}

int			is_all_digits(char *line)
{
	int		i;

	i = -1;
	if (!line)
		return (0);
	while (line[++i])
	{
		if (line[i] >= '0' && line[i] <= '9')
			continue;
		else
			return (0);
	}
	return (1);
}

int			split_bits(char *line, char c)
{
	char	**split;
	int		i;
	int		j;

	i = -1;
	j = -1;
	split = NULL;
	if (!(split = ft_strsplit(line,  c)))
		return (0);
	while (split[++i])
		continue ;
	while (split[++j])
		ft_strdel(&split[j]);
	return (i);
}

void		del_str_arr(char **to_delete)
{
	int		i;

	i = -1;
	if (to_delete)
	{
		while(to_delete[++i])
			ft_strdel(&to_delete[i]);
		free(to_delete);
	}
}