/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samymone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 16:23:08 by samymone          #+#    #+#             */
/*   Updated: 2019/10/27 16:23:10 by samymone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
#define LEMIN_H

#include "./libft/includes/libft.h"
#include "./libft/includes/get_next_line.h"
#include <stdlib.h>

typedef struct 		s_room
{
	int 			num;	//порядковый номер комнаты
	int 			x;		//x координата
	int 			y;		//y координата
	int 			links;	//колическтво связей с другими комнатами
	int 			level;	//уровень комнаты
	struct s_ant	*ant;
	int 			is_valid; 	//стоит ли идти по этой связи, по умолчанию все равно 0
}					t_room;

typedef struct 		s_map
{
	t_room			*current;	//комната, в которой мы сейчас находимся
	int				linked;		//со сколькими комнатами связана
	t_room			*prev;		//указатель на предыдущую комнату, для самой первой указатель == NULL
	t_room			*next;		//указатель на следующие комнаты, для последней указатель == NULL. Для начала маллочим память
								//next(имя любое) = malloc(sizeof(t_room) * t_room->links. Оращаться через next[0], next[1] итд

	int 			start;		//флаг начала заполнения структуры
	int				ants;		//количество муравьев
	struct s_ant	*first;		//первый муравей
	struct s_ant	*last;		//последний муравей
}					t_map;

typedef struct		s_ant
{
	int 			num;		//порядковый номер муравья
	t_room 			*curr_room;	//в какой комнате он сейчас находится
	struct s_ant	*next;		//указатель на следующего муравья
	struct s_ant	*prev;
}					t_ant;

t_map				*parse_input(char **av, t_map *map);
t_map				*structure_filling(char *line, t_map *map);
void 				ft_error(void);
void 				free_map(t_map *map);
void 				free_ant(int i, t_ant *ant);
t_ant				*ant_colony_creation(int quant, t_map *map);

#endif
