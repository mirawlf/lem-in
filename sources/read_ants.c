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
	if (is_all_digits(line) && (ft_atoi(line) * 10 / 10 == ft_atoi(line)))
		return (ft_atoi(line));
	return (0);
}

int				read_ants(t_main *data)
{
	char		*line;
	int			ret;

	while ((ret = get_next_line(0, &line)) > 0)
	{
		if (line)
		{
			if (!data->mapfile->text)
				data->mapfile->text = ft_strdup(line);
			if (is_comment(line))
				continue;
			else
			{
				if (!is_ants(line))
					return (del_line_and_return(line, 0));
				data->ants = is_ants(line);
				break ;
			}
		}
	}
	return ((ret > 0) ? del_line_and_return(line, 1) :
	del_line_and_return(line, 0));
}
