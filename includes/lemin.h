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

#include "../libft/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include "../libft/get_next_line.h"

typedef struct		s_room
{
	char			*name;
	int				x;
	int				y;
	int				level;
	int				neighbours;
	int				is_dead_end;
	int				steps;
	int				is_part_of_path;
	int				inputs;
	int				outputs;
	struct s_room	*where;
	struct s_room	*from;
	struct s_room	*next;
	struct s_ant	*ant;
}					t_room;

typedef struct		s_ant
{
	int				num;
	t_room			*curr_room;
	struct s_ant	*next;
//	struct s_ant	*prev;
}					t_ant;

typedef struct		s_link
{
	t_room			*first_room;
	t_room			*second_room;
	int				checked;
	int				is_valid;
	int				has_pair;

	struct s_link	*next;
}					t_link;

typedef struct		s_path
{
	t_room			*current;
	struct s_path	*next;
}					t_path;

typedef struct		s_toend
{
	t_path			*path;
}					t_toend;

typedef struct		s_fromstart
{
	t_path			*path;
}					t_fromstart;

typedef struct		s_main
{
	int				ants;
	int				original_ants;
	t_room			*start;
	t_room			*end;
	t_ant			*first_ant;
	t_ant			*last_ant;
	char			*line;
	t_room			*all_rooms_here;
	t_link			*all_links_here;
	int				reached_end;
	int				rooms;
	t_path			*paths;
	t_path			**path_array;
	int				paths_amount;
	int				start_connections;
	int				end_connections;
	int				fd;
	char			*courier;
	t_toend			*endway;
	t_fromstart		*startway;
	int				print_paths;
	char			*file;
}					t_main;

/*
** reading input data
*/

int					read_ants(t_main *data);
int					read_links(t_main *data);
int					read_rooms(t_main *data);

/*
** validation
*/

int					is_link(char *line);
int					is_room(char *line);
int					is_comment(char *line);
int					valid_coords(t_room *room, t_room *list);
int					duplicate_links(t_link *link, t_main *data);

/*
** algo functions
*/

void				main_algo_part(t_main *map);
void				dead_ends(t_main *map);
void				next_levels(t_main *map, int max_curr_lvl);
void				count_inputs_and_outputs(t_main *map);
void				start_end_link(t_main *main);
void				start_searching(t_room *room, t_main *map);
void				search_previous_room(t_room *current, t_main *map);
int					has_already_path(t_room *room, t_room *current);
t_room				*best_variant(t_room *current, t_room *variant,
					t_main *map);
t_room				*best_variant2(t_room *current, t_room *variant, t_main *map);
t_room				*best_variant3(t_room *current, t_room *variant,
									 t_main *map);
t_room				*best_variant4(t_room *current, t_room *variant,
									 t_main *map);
void				remake_paths2(t_room *best, t_room *current, t_main *map);
void				auxiliary(t_room *first, t_room *second,
					t_link *link, t_main *map);
int					compare_paths(t_room *best, t_room *current);
void				remake_paths(t_room *current, t_main *map);
void				free_path(t_room *current, t_main *map);
void				second_rooms(t_room *room, t_main *map);
void				possible_ways(t_room *room, t_main *map);
void				search_intersections(t_main *map);
void				search_next_room(t_room *current, t_main *map);
t_room				*best_room(t_room *current, t_room *variant, t_main *map);
int					check_length(t_room *current, t_room *prev);
void				try_to_change_tails(t_room *current, t_main *map);
void				search_left_paths(t_main *map);
void				auxiliary2(t_room *from, t_room *where, t_link *link, t_main *map);
int					has_link(t_room *current, t_room *possible, t_link *linklist);
int					reach_end(t_room *room,  t_room *end);
void				new_tails(t_main *map);
void 				new_heads(t_main *map);
void				number_of_path_increasing(t_main *map);

/*
** ants' movements
*/

void				count_steps(t_main *map);
t_path				**make_path_array(t_main *main);
void				lets_go(t_main *map);
int					can_i_go_please(t_room *room);
void				make_oneway_step(t_main  *main, t_path *best_path);
void				make_step(t_main  *main, t_path **path_array);
int					make_start_step(t_ant *ant, t_main *main);
t_ant				*make_normal_step(t_ant *ant, t_main *main);
void				print_step(int ant_num, char *room_name, t_main *main);
t_ant				*del_ant(t_ant *ant, t_main *main);

/*
** utils
*/

void				del_str_arr(char **to_delete);
int					split_bits(char *line, char c);
int					is_all_digits(char *line);
int					del_line_and_return(char *line, int ret);


/*
** freeshing
*/

void				free_rooms(t_room *room, t_room *start, t_room *end);
//void				freeshing(t_main *map);
t_main				*parse_input(t_main *map);
t_main				*structure_filling(t_main *map);
int 				ft_error(const char *error);
t_main				*ant_colony_creation(int quant, t_main *map);

#endif
