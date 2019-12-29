/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samymone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 16:23:08 by samymone          #+#    #+#             */
/*   Updated: 2019/12/22 17:13:51 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
#define LEMIN_H

#include "./libft/includes/libft.h"
#include "./libft/includes/get_next_line.h"
#include <stdlib.h>

typedef struct 		s_room
{
	char 			*name;	//название комнаты?
	int 			x;		//x координата
	int 			y;		//y координата
	struct s_room	*next;
}					t_room;

/*typedef struct 		s_map
{
	t_room			*current;	//комната, в которой мы сейчас находимся
	int				linked;		//со сколькими комнатами связана
	t_room			**prev;		//указатель на предыдущую комнату, для самой первой указатель == NULL
	t_room			**next;		//указатель на следующие комнаты, для последней указатель == NULL. Для начала маллочим память
								//next(имя любое) = malloc(sizeof(t_room) * t_room->links. Оращаться через next[0], next[1] итд

	int 			start;		//флаг начала заполнения структуры
	int				ants;		//количество муравьев
	struct s_ant	*first;		//первый муравей
	struct s_ant	*last;		//последний муравей
}					t_map;*/

typedef struct		s_ant
{
	int 			num;		//порядковый номер муравья
	t_room 			*curr_room;	//в какой комнате он сейчас находится
	struct s_ant	*next;		//указатель на следующего муравья
	struct s_ant	*prev;
}					t_ant;

typedef struct 		s_link////структура со связью
{
	t_room			*first_room;////название говорит за себя
	t_room			*second_room;
	struct s_link	*next;
}					t_link;

typedef struct		s_main
{
	int 			ants;/////кол-во муравьев
	t_room			*start;
	t_room			*end;
	t_ant			*first_ant;		//первый муравей
	t_ant			*last_ant;
	char 			*line;
	t_room			*all_rooms_here;
	t_link			*all_links_here;
}					t_main;

/**
 * freeshing
 */
void		free_rooms(t_room *room);

t_main				*parse_input(char **av, t_main *map);
t_main				*structure_filling(char *line, t_main *map, int fd);
void 				ft_error(char *error);
void 				free_map(t_main *map);
void 				free_ant(int i, t_ant *ant);
t_ant				*ant_colony_creation(int quant, t_main *map);

/**
 * service functions
 */
void				free_split(char **split);

/**
 * validation
 */
char 	**check_connection(char *line);
int 	check_and_write_ants(char *line, t_main *map);
int 	check_command(char *line);
int 	line_exists(char *line);
int 	check_comment(char *line);
/**
 * reading
 */
t_room		*create_room(char *line);
t_room 	*read_rooms(t_main *main, int fd);
t_link	*get_me_links(t_main *main, int fd, t_room *room);

#endif
