##
## EPITECH PROJECT, 2026
## Cuddle
## File description:
## Makefile for the cuddle project
## to handle compilation and cleaning.
##

NAME = libcuddle.a
CC = epiclang
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lm

SRC = src/types.c \
	src/dataframe.c \
	src/rows_and_columns.c \
	src/basics.c \
	src/sorting.c \
	src/filter.c \
	src/aggregation.c \
	src/transformation.c \
	src/utilities.c \
	src/helper.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
