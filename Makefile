NAME = lem-in

SRC_DIR = sources
HDR_DIR = includes
OBJ_DIR = objects

LFT = libft.a
LFT_DIR = libft

SRC_FILES = after_finding_paths.c ant_steps.c ants_run_like_shit.c best_next.c \
            best_room_definition.c  best_previous_room1.c  best_previous_room2.c \
            best_previous_room3.c best_previous_room4.c freeshing.c go.c last_passageway.c lemin.c \
            move_one_way.c read_ants.c read_links.c read_rooms.c \
            rooms_description.c search_intersections.c search_paths.c second_searching.c \
            utils.c valid.c ways_modification.c parser_and_filling.c path_or_its_part_is_found.c \
            remake_paths.c new_tails.c new_heads.c start_end_link.c

SRCS = $(addprefix $(SRC_DIR)/,$(SRC_FILES))
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
DEPS = $(OBJS:.o=.c)

CC = gcc
RM = rm -rf
FLGS = -Wall -Wextra -Werror
IFLGS = -I $(HDR_DIR) -I $(LFT_DIR)
LFLGS = -L $(LFT_DIR) -lft

.PHONY: all clean fclean re

all: $(NAME)

$(LFT_DIR)/$(LFT):
	$(MAKE) -C $(LFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLGS) $(DFLGS) -c -o $@ $< $(IFLGS)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(NAME): $(LFT_DIR)/$(LFT) $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LFLGS)

clean:
	$(MAKE) -C $(LFT_DIR) clean
	$(RM) $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LFT_DIR) fclean
	$(RM) $(NAME)

re: fclean all