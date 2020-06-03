/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 20:35:50 by student           #+#    #+#             */
/*   Updated: 2020/06/03 20:35:52 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void			del_str_arr(char **to_delete)
{
	int			i;

	i = -1;
	if (to_delete)
	{
		while (to_delete[++i])
			ft_strdel(&to_delete[i]);
		free(to_delete);
	}
}

void			new_line_for_mapfile(t_mapfile *tmp, char *line)
{
	while (tmp->next)
		tmp = tmp->next;
	if (!(tmp->next = ft_memalloc(sizeof(t_mapfile)))
		|| !(tmp->next->text = ft_strdup(line)))
		ft_error("ERROR");
}
