/*
** EPITECH PROJECT, 2026
** Cuddle
** File description:
** Dataframe utilities.
*/

#include "dataframe.h"

void copy_data(dataframe_t *new_df, int i_new_df,
    dataframe_t *df, int i_old_df)
{
    int size;

    for (int j = 0; j < df->nb_columns; j++) {
        if (!df->data[i_old_df][j]) {
            new_df->data[i_new_df][j] = NULL;
            continue;
        }
        if (new_df->column_types[j] == STRING) {
            new_df->data[i_new_df][j] = strdup((char *)df->data[i_old_df][j]);
            continue;
        }
        if (new_df->column_types[j] == FLOAT)
            size = sizeof(float);
        else
            size = sizeof(int);
        new_df->data[i_new_df][j] = malloc(size);
        if (new_df->data[i_new_df][j])
            memcpy(new_df->data[i_new_df][j], df->data[i_old_df][j], size);
    }
}

dataframe_t *init_new_df(dataframe_t *df, int nb_rows)
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
