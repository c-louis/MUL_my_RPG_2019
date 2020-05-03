##
## EPITECH PROJECT, 2019
## project
## File description:
## Makefile
##

SRC	=	src/main.c			\
		src/event.c			\
		src/loop.c			\
		src/init.c			\
		src/clean.c			\
		src/particle/engine.c		\
		src/particle/anim.c		\
		src/particle/system.c		\
		src/particle/part.c		\
		src/particle/buffer.c		\
		src/particle/desc/desc.c	\
		src/particle/desc/move.c

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
