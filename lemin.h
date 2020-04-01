/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samymone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 16:23:08 by samymone          #+#    #+#             */
/*   Updated: 2020/03/15 21:29:55 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
#define LEMIN_H

#include "./libft/libft.h"
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
	int 			has_pair;
	int 			steps;
	int 			is_part_of_path;
	int 			inputs;
	int 			outputs;
	int             equals; //input or output for rooms of same level
	struct s_room	*where;
	struct s_room	*from;
	struct s_room	*next;
	struct s_ant	*ant;
}					t_room;

typedef struct		s_ant
{
	int 			num;		//порядковый номер муравья
	t_room 			*curr_room;	//в какой комнате он сейчас находится
	struct s_ant	*next;		//указатель на следующего муравья
//	struct s_ant	*prev;
}					t_ant;

typedef struct 		s_link////структура со связью
{
	t_room			*first_room;////название говорит за себя
	t_room			*second_room;
	int 			checked;
	int 			is_valid;
	int 			has_pair;

	struct s_link	*next;
}					t_link;

typedef struct 		s_path
{
	t_room 			*current;
	struct s_path	*next;
}					t_path;

typedef struct      s_toend
{
    t_room          *current;
    struct s_toend  *next;
}                   t_toend;

typedef struct      s_fromstart
{
    t_room          *current;
    struct s_fromstart  *next;
}                   t_fromstart;

typedef struct		s_main
{
	int 			ants;/////кол-во муравьев
	int 			original_ants;
	t_room			*start;
	t_room			*end;
	t_ant			*first_ant;		//первый муравей
	t_ant			*last_ant;
	char 			*line;
	t_room			*all_rooms_here;
	t_link			*all_links_here;
	int 			reached_end;
	int 			rooms;
	t_path			*paths;
	t_path 			**path_array;
	int 			paths_amount;
	int 			start_connections;
	int				end_connections;
	int 			del_me_fd;
	char 			*courier;
	t_toend         *endway;
	t_fromstart     *startway;
}					t_main;

/**
 * freeshing
 */
void				free_rooms(t_room *room);

t_main				*parse_input(char **av, t_main *map);
t_main				*structure_filling(t_main *map);
int 				ft_error(const char *error);
void 				free_map(t_main *map);
void 				free_ant(int i, t_ant *ant);
t_ant				*ant_colony_creation(int quant, t_main *map);


/**
 * validation
 */
int 	is_step(char *step);//////////////check more validation with the old shit folder; this one comes from viz, might be not good
int 	is_link(char *line);
int 	is_room(char *line);
int 	is_comment(char *line);
int 	valid_coords(t_room *room, t_room *list);
int 	duplicate_links(t_link *link, t_main *data);

/**
 * reading
 */
int 	read_ants(t_main *data);
int 	read_links(t_main *data);
int 	read_rooms(t_main *data);



/*
 * algo
 */
void				*determine_levels(t_main *map);
void 				determine_level(t_main *map);
void				*except_excess_links(t_link *links, t_room *rooms);
int 				was_checked(t_room *first, t_room *second, t_link *links);

void				search_necessary_rooms(t_main *map);
void				search_previous_room(t_room *current, t_main *map);
void 				*count_steps(t_main *map);
//void				auxiliary(t_room *first, t_room *second, t_link *link, t_main *map);
void 				lets_go(t_main *map);
//void 				*sort_paths(t_path *paths);
int 				is_sorted(t_path *paths);

/*
 * ants will move now
 */
void 	print_step(int ant_num, char *room_name, t_main *main);
t_path	**make_path_array(t_main *main);
t_ant 	*make_normal_step(t_ant *ant, t_main *main);
int 	can_i_go_please(t_room *room);
int 	make_start_step(t_ant *ant, t_main *main);
void		make_step(t_main  *main, t_path **path_array);
t_ant 	*del_ant(t_ant *ant, t_main *main);
void		make_oneway_step(t_main  *main, t_path *best_path);
void		check_end_connections(t_main *map);
//void		auxiliary(t_room *first, t_room *second, t_link *link, t_main *map);
void 		search_paths(t_main *map);
void		next_levels(t_main *map, int max_curr_lvl);
void		milky_way(t_main *map, int level);
void		delete_useless_links(t_main *map);
void		count_inputs_and_outputs(t_main *map);
void		delete_bad_outputs(t_main *map);
void		start_searching(t_room *room, t_main *map);
void 		exclude_forks(t_main * map);
void 		delete_other_input_rooms(t_room *current, t_room *second, t_main *map);
t_room		*best_variant(t_room *current, t_room *variant, t_main *map);
void			dead_ends(t_main *map);
void			free_path(t_room *current, t_main *map);
void		take_a_glimse_of_paths(t_main *map);
int 			compare_paths(t_room *best, t_room *current);

/*
 * utils
 */
void		del_str_arr(char **to_delete);//////////эти функции делают одно и то же, надо бы убрать одну из них, ту, что похуже
void				free_split(char **split);
int 	split_bits(char *line, char e);
int		is_all_digits(char *line);
int 	del_line_and_return(char *line, int ret);
int 				print_line(int ret, char *line);
void        search_intersections(t_main *map);
void             search_next_room(t_room *current, t_main *map);
t_room      *best_room(t_room *current, t_room *variant, t_main *map);

#endif
