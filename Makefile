##
## EPITECH PROJECT, 2026
## Cuddle - Bootstrap
## File description:
## Makefile for the cuddle bootstrap
## to handle compilation and cleaning.
##

CC = epiclang
CPPFLAGS = -I./include
CFLAGS = -Wall -Wextra -Werror

SRC = src/main.c \
	src/types.c \
	src/dataframe.c

OBJ = $(SRC:.c=.o)
NAME = cuddle

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all