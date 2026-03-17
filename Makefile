##
## EPITECH PROJECT, 2026
## Cuddle
## File description:
## Makefile for the cuddle bootstrap
## to handle compilation and cleaning.
##

NAME = libcuddle.a
CC = epiclang
CPPFLAGS = -I./include
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
	ranlib $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: all clean fclean re