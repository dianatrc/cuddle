/*
** EPITECH PROJECT, 2026
** Cuddle - Bootstrap
** File description:
** Main header file for
** structures and function declarations.
*/

#ifndef DATAFRAME_H_

    #define DATAFRAME_H_

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

typedef enum {
    BOOL,
    INT,
    UINT,
    FLOAT,
    STRING,
    UNDEFINED
} column_type_t;

typedef struct {
    int nb_rows;
    int nb_columns;
    char **column_names;  // array of column names
    column_type_t *column_types;  // array of column types
    void ***data;  // 2d array of data values
} dataframe_t;

typedef struct {
    int nb_rows;
    int nb_columns;
} dataframe_shape_t;

column_type_t determine_str_type(char *str);
void *convert_to_type(char *str, column_type_t type);

void get_column_names(dataframe_t *df, FILE *fd, const char *separator);
void read_lines(dataframe_t *df, FILE *fd, const char *separator);
void determine_columns_type(dataframe_t *df);

#endif
