/*
** EPITECH PROJECT, 2026
** Cuddle
** File description:
** Main and helper functions
** for the transformation.
*/

#include "dataframe.h"

void *multiply(void *value)
{
    int *new_value = malloc(sizeof(int));

    if (!new_value)
        return NULL;
    *new_value = *(int *)value * 2;
    return new_value;
}

dataframe_t *df_apply(dataframe_t *df, const char *column,
    void *(*apply_func)(void *value))
{
    dataframe_t *new_df;
    int col;
    void *tmp;

    if (!df || !column || !apply_func || df->nb_rows == 0)
        return NULL;
    col = get_column_index(df, column);
    if (col == -1)
        return NULL;
    new_df = df_head(df, df->nb_rows);
    if (!new_df)
        return NULL;
    for (int i = 0; i < new_df->nb_rows; i++) {
        if (!new_df->data[i][col])
            continue;
        tmp = new_df->data[i][col];
        new_df->data[i][col] = apply_func(tmp);
        free(tmp);
    }
    return new_df;
}

static char *value_to_str(void *value, column_type_t type)
{
    char buffer[256];

    if (!value)
        return NULL;
    if (type == STRING)
        return strdup((char *)value);
    if (type == BOOL) {
        if (*(int *)value)
            return strdup("true");
        else
            return strdup("false");
    }
    if (type == FLOAT) {
        sprintf(buffer, "%.2f", *(float *)value);
    } else if (type == UINT) {
        sprintf(buffer, "%u", *(unsigned int *)value);
    } else {
        sprintf(buffer, "%d", *(int *)value);
    }
    return strdup(buffer);
}

static int process_type_row(dataframe_t *new_df, dataframe_t *df,
    int i, int column_index)
{
    char *str_value;
    column_type_t type = df->column_types[column_index];
    column_type_t target_type = new_df->column_types[column_index];

    new_df->data[i] = calloc(df->nb_columns, sizeof(void *));
    if (!new_df->data[i])
        return 0;
    for (int j = 0; j < df->nb_columns; j++) {
        if (j != column_index) {
            new_df->data[i][j] = copy_value(df->data[i][j],
                df->column_types[j]);
            continue;
        }
        str_value = value_to_str(df->data[i][j], type);
        new_df->data[i][j] = convert_to_type(str_value, target_type);
        free(str_value);
        if (!new_df->data[i][j])
            return 0;
    }
    return 1;
}

dataframe_t *df_to_type(dataframe_t *df, const char *column,
    column_type_t downcast)
{
    int column_index;
    dataframe_t *new_df;

    if (!df || !column)
        return NULL;
    column_index = get_column_index(df, column);
    if (column_index == -1)
        return NULL;
    new_df = init_new_df(df, df->nb_rows);
    if (!new_df)
        return NULL;
    new_df->column_types[column_index] = downcast;
    for (int i = 0; i < df->nb_rows; i++) {
        if (!process_type_row(new_df, df, i, column_index)) {
            df_free(new_df);
            return NULL;
        }
    }
    return new_df;
}
