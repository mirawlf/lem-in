/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 18:09:11 by student           #+#    #+#             */
/*   Updated: 2020/05/20 18:09:13 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

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
	if (!(split = ft_strsplit(line, c)))
		return (0);
	while (split[++i])
		continue ;
	while (split[++j])
		ft_strdel(&split[j]);
	return (i);
}
