LEMIN = lemin

#FLAGS = -Wall -Wextra -Werror

MAKE = make

SRC_FILES =  ant_steps.c ants_run_like_shit.c check_end_connections.c tips_for_algo.c \
        filling.c find_yourself_a_room.c freeshing.c get_me_paths_lawd.c go.c lemin.c \
        levels_and_links.c move_one_way.c path_finder.c redrum.c after_finding_paths.c \
        search_paths.c soulmates.c utils.c valid.c best_room_definition.c

INCL_FILE = lemin.h

SRC = ./sources/

INCL = ./includes/

LIB = ./libft/libft.a

OBJ = $(SRC:.c=.o)


!!!!!!!!!!!!!
дописать addprefix и исправить src
!!!!!!!!!!!!!

all:$(LEMIN)

%.o: %.c
	    gcc $(FLAGS) -c -o $@ $< -g

$(LEMIN): $(LIB) $(OBJ)
	    gcc -g -I $(INCL) $(LIB) -o $(LEMIN) $(SRC)

$(LIB):
	    $(MAKE) -C ./libft/

clean:
	    $(MAKE) clean -C ./libft
		rm -f $(OBJ)

fclean: clean
	    $(MAKE) fclean -C ./libft
		rm -f $(LEMIN)

re: fclean all