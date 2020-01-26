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
	int 			x;		//x координата комнаты
	int 			y;		//y координата комнаты
	int 			level;  // 1 Step 1 шаг
	int 			was_checked; // проверка Level == 1
	int 			neighbours; //количество соседей
	int 			is_dead_end; //если тупик 1
	int				is_part_of_path; //является ли комната частью пути
	int 			num_of_path;
	struct s_room	*where;
	struct s_room	*from;
	struct s_room	*next;
}					t_room;

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
	int 			checked;
	int 			is_valid;

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
	int 			path;
	int 			max_current_level;
}					t_main;

typedef struct 		s_path
{
	t_room 			*current;
	int 			steps;
	struct s_path	*next;
}					t_path;

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

/*
 * algo
 */
void		*determine_levels(t_main *map);
void 		determine_level(t_main *map);
void		*except_excess_links(t_link *links, t_room *rooms);
int 		was_checked(t_room *first, t_room *second, t_link *links);

void		*search_necessary_rooms(t_main *map);
void		*search_previous_room(t_room *current, t_main *map);
void 		sequence_of_rooms(t_path *path, t_main *map, int i);


#endif
