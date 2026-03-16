##
## EPITECH PROJECT, 2026
## Cuddle
## File description:
## Makefile for the cuddle bootstrap
## to handle compilation and cleaning.
##

CC = epiclang
CPPFLAGS = -I./include
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lm

SRC = src/main.c \
	src/types.c \
	src/dataframe.c \
	src/rows_and_columns.c \
	src/basics.c \
	src/sorting.c \
	src/filter.c \
	src/transformation.c \
	src/utilities.c \

OBJ = $(SRC:.c=.o)
NAME = cuddle

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LDFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all