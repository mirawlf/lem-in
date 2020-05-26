/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samymone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 12:02:18 by samymone          #+#    #+#             */
/*   Updated: 2019/05/09 14:48:08 by samymone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	discharge(size_t i, size_t j)
{
	size_t m;
	size_t k;
	size_t g;

	m = 10;
	k = 1;
	g = 0;
	while (g < (i - j))
	{
		k *= m;
		g++;
	}
	return (k);
}

static char		*string(size_t i, size_t n3, int n)
{
	size_t	j;
	char	*s;

	j = 0;
	if (!(s = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	while (j < i)
	{
		if (j == 0 && n < 0)
			s[j] = '-';
		else
			s[j] = (n3 % discharge(i, j) / (0.1 * discharge(i, j))) + '0';
		j++;
	}
	s[j] = '\0';
	return (s);
}

char			*ft_itoa(int n)
{
	size_t	n2;
	size_t	i;
	size_t	n3;

	n2 = 0;
	i = 0;
	if (n < 0)
	{
		i++;
		n2 = (unsigned)(n * -1);
	}
	else
		n2 = n;
	n3 = n2;
	while (n2 > 0 || (n2 == 0 && i < 1))
	{
		i++;
		n2 /= 10;
	}
	return (string(i, n3, n));
}
