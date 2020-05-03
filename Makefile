##
## EPITECH PROJECT, 2019
## project
## File description:
## Makefile
##

SRC	=	src/main.c	\
		src/event.c	\
		src/loop.c	\
		src/init.c	\
		src/clean.c	\
		src/file.c 	\
		src/light/intersect.c	\
		src/light/init.c		\
		src/light/raycast.c		\
		src/light/update.c		\
		src/light/utils.c		\
		src/light/clean_ray.c	\
		src/map/map_read.c		\
		src/map/light.c			\
		src/map/room.c			\
		src/map/wall.c			\
		src/map/information.c	\
		src/map/init_entity.c	\
		src/map/entity.c		\
		src/enemies/item.c		\
		src/enemies/enemy.c			\
		src/enemies/enemy_loot.c	\
		src/enemies/enemy_body.c	\
		src/enemies/item_body.c		\
		src/enemies/static_read.c	\
		src/player/movement.c		\
		src/player/rotation.c		\
		src/player/end_room.c		\
		src/entity/draw.c			\
		src/entity/math_utils.c		\
		src/entity/movement.c		\
		src/entity/copy.c			\
		src/rooms/getter.c			\
		src/rooms/debugger.c		\
		src/bank/getter.c			\
		src/hud/init.c				\
		src/hud/utils.c				\

OBJ	=	$(SRC:.c=.o)

NAME	=	my_rpg

CFLAGS	=	-Iinclude -Llib -lmy -lcsfml-graphics -lcsfml-window -lcsfml-system -lcsfml-audio -lm

all:
	$(MAKE) -C lib/my --no-print-directory
	$(MAKE) -C lib/my clean --no-print-directory
	$(MAKE) $(NAME) --no-print-directory

$(NAME):$(OBJ)
	gcc -o $(NAME) $(OBJ) $(CFLAGS)

debug:
	gcc -g -o $(NAME) $(SRC) $(CFLAGS)

tests_run:
	$(MAKE) -C tests/ --no-print-directory
	./unit-tests

clean:
	rm -f $(OBJ)
	$(MAKE) -C ./tests clean --no-print-directory

fclean:	clean
	rm -f lib/my/libmy.a lib/libmy.a
	rm -f $(NAME)
	$(MAKE) -C ./tests fclean --no-print-directory

re:	fclean all
