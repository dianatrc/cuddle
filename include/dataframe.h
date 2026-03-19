/*
** EPITECH PROJECT, 2026
** Cuddle
** File description:
** Main header file for
** structures and function declarations.
*/

#ifndef DATAFRAME_H_

    #define DATAFRAME_H_

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <math.h>
    #include <stdbool.h>

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
    char *separator;
    char **column_names;  // array of column names
    column_type_t *column_types;  // array of column types
    void ***data;  // 2d array of data values
} dataframe_t;

typedef struct {
    int nb_rows;
    int nb_columns;
} dataframe_shape_t;

typedef struct {
    int count;
    double mean;
    double std;
    double min;
    double max;
} statistics_t;

// types.c
column_type_t determine_str_type(char *str);
void *convert_to_type(char *str, column_type_t type);
// dataframe.c
dataframe_t *create_df(void);
dataframe_t *df_read_csv(const char *filename, const char *separator);
int df_write_csv(dataframe_t *df, const char *filename);
void copy_data(dataframe_t *new_df, int i_new_df,
    dataframe_t *df, int i_old_df);
dataframe_t *init_new_df(dataframe_t *df, int nb_rows);
// rows_and_columns.c
void get_column_names(dataframe_t *df, FILE *fd, const char *separator);
void read_lines(dataframe_t *df, FILE *fd, const char *separator);
void determine_columns_type(dataframe_t *df);
int get_column_index(dataframe_t *df, const char *column);
// basics.c
dataframe_t *df_head(dataframe_t *df, int nb_rows);
dataframe_t *df_tail(dataframe_t *df, int nb_rows);
dataframe_shape_t df_shape(dataframe_t *df);
void df_info(dataframe_t *df);
void df_describe(dataframe_t *df);
// sorting.c
bool compare_int(void *value1, void *value2);
bool compare_float(void *value1, void *value2);
bool compare_string(void *value1, void *value2);
dataframe_t *df_sort(dataframe_t *df, const char *column,
    bool (*sort_func)(void *value1, void *value2));
// filter.c
bool filter_function(void *value);
dataframe_t *df_filter(dataframe_t *df, const char *column,
    bool (*filter_function)(void *value));
// aggregation.c
void *agg_func(void **values, int nb_values);
dataframe_t *df_groupby(dataframe_t *df, const char *aggregate_by,
    const char **to_aggregate, void *(*agg_func)(void **values, int nb_values));
// transformation.c
void *multiply(void *value);
dataframe_t *df_apply(dataframe_t *df, const char *column,
    void *(*apply_func)(void *value));
dataframe_t *df_to_type(dataframe_t *df, const char *column,
    column_type_t downcast);
// utilities.c
void *df_get_value(dataframe_t *df, int row, const char *column);
void **df_get_values(dataframe_t *df, const char *column);
void **df_get_unique_values(dataframe_t *df, const char *column);
void df_free(dataframe_t *df);
// helper.c
char *to_lowercase(const char *str);
int bool_from_str(char *str, int *value);
void *copy_value(void *value, column_type_t type);
// join.c
dataframe_t *df_join(dataframe_t *df1, dataframe_t *df2, const char *column);

#endif
