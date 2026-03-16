/*
** EPITECH PROJECT, 2026
** Cuddle - Bootstrap
** File description:
** Main entry point for the
** cuddle bootstrap.
*/

#include "../include/dataframe.h"

static void copy_data(dataframe_t *new_df, int i_new_df,
    dataframe_t *df, int i_old_df)
{
    int size;

    for (int j = 0; j < df->nb_columns; j++) {
        if (new_df->column_types[j] == STRING) {
            new_df->data[i_new_df][j] = strdup((char *)df->data[i_old_df][j]);
            continue;
        }
        if (new_df->column_types[j] == FLOAT)
            size = sizeof(float);
        else
            size = sizeof(int);
        new_df->data[i_new_df][j] = malloc(size);
        memcpy(new_df->data[i_new_df][j], df->data[i_old_df][j], size);
    }
}

static dataframe_t *init_new_df(dataframe_t *df, int nb_rows)
{
    dataframe_t *new_df = create_df();

    if (!new_df)
        return NULL;
    new_df->nb_rows = nb_rows;
    new_df->nb_columns = df->nb_columns;
    new_df->column_names = malloc(sizeof(char *) * df->nb_columns);
    new_df->column_types = malloc(sizeof(column_type_t) * df->nb_columns);
    new_df->data = malloc(sizeof(void **) * nb_rows);
    for (int i = 0; i < df->nb_columns; i++) {
        new_df->column_names[i] = strdup(df->column_names[i]);
        new_df->column_types[i] = df->column_types[i];
    }
    return new_df;
}

dataframe_t *df_head(dataframe_t *df, int nb_rows)
{
    dataframe_t *new_df;

    if (!df || nb_rows <= 0)
        return NULL;
    if (nb_rows > df->nb_rows)
        nb_rows = df->nb_rows;
    new_df = init_new_df(df, nb_rows);
    if (!new_df)
        return NULL;
    for (int i = 0; i < nb_rows; i++) {
        new_df->data[i] = malloc(sizeof(void *) * df->nb_columns);
        copy_data(new_df, i, df, i);
    }
    return new_df;
}

dataframe_t *df_tail(dataframe_t *df, int nb_rows)
{
    dataframe_t *new_df;
    int start_row = 0;

    if (!df || nb_rows <= 0)
        return NULL;
    if (nb_rows > df->nb_rows)
        nb_rows = df->nb_rows;
    new_df = init_new_df(df, nb_rows);
    if (!new_df)
        return NULL;
    start_row = df->nb_rows - nb_rows;
    for (int i = 0; i < nb_rows; i++) {
        new_df->data[i] = malloc(sizeof(void *) * df->nb_columns);
        copy_data(new_df, i, df, start_row + i);
    }
    return new_df;
}

dataframe_shape_t df_shape(dataframe_t *df)
{
    dataframe_shape_t shape = {df->nb_rows, df->nb_columns};

    return shape;
}

void df_info(dataframe_t *df)
{
    char *types[] = {"bool", "int", "uint", "float", "string", "undefined"};

    printf("%d columns:\n", df->nb_columns);
    for (int i = 0; i < df->nb_columns; i++) {
        printf("- %s: %s\n", df->column_names[i], types[df->column_types[i]]);
    }
}

void df_describe(dataframe_t *df)
{
    if (!df || df->nb_rows == 0)
        return;
    for (int i = 0; i < df->nb_columns; i++) {
        if (df->column_types[i] == BOOL || df->column_types[i] == STRING
            || df->column_types[i] == UNDEFINED)
            continue;
        printf("Column: %s\n", df->column_names[i]);
    }
}
