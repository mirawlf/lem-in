/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 17:03:37 by student           #+#    #+#             */
/*   Updated: 2020/05/20 17:03:39 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int		is_ants(char *line)
{
	if (is_all_digits(line))
		return (ft_atoi(line));
	return (0);
}

int				read_ants(t_main *data)
{
	char		*line;
	int			ants;

	ants = 0;
	while (get_next_line(0, &line) > 0)
	{
		if (line)
		{
			if (is_comment(line))
				continue;
			else
			{
				ants = is_ants(line);
				if (!ants)
					del_line_and_return(line, 0);
				data->ants = ants;
				break ;
			}
		}
	}
	return (del_line_and_return(line, 1));
}
