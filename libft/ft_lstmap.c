/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samymone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 15:34:13 by samymone          #+#    #+#             */
/*   Updated: 2019/05/04 18:04:47 by samymone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*fresh;

	if (lst == NULL)
		return (NULL);
	fresh = f(lst);
	if (lst && f)
	{
		fresh = f(lst);
		if ((*lst).next)
			(*fresh).next = ft_lstmap((*lst).next, f);
	}
	return (fresh);
}
