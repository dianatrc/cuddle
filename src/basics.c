/*
** EPITECH PROJECT, 2026
** Cuddle - Bootstrap
** File description:
** Main entry point for the
** cuddle bootstrap.
*/

#include "../include/dataframe.h"

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
    char *types[] = {"bool", "int", "unsigned int",
        "float", "string", "undefined"};

    printf("%d columns:\n", df->nb_columns);
    for (int i = 0; i < df->nb_columns; i++) {
        printf("- %s: %s\n", df->column_names[i], types[df->column_types[i]]);
    }
}

static double get_value(void *data, column_type_t type)
{
    if (type == FLOAT)
        return (double)(*(float *)data);
    return (double)(*(int *)data);
}

static void update_min_max(statistics_t *stats, double value)
{
    if (stats->count == 0 || value < stats->min)
        stats->min = value;
    if (stats->count == 0 || value > stats->max)
        stats->max = value;
}

static void calculate_statistics(dataframe_t *df, int col, statistics_t *stats)
{
    double sum = 0;
    double sq_sum = 0;
    double value;

    stats->count = 0;
    for (int i = 0; i < df->nb_rows; i++) {
        if (!df->data[i][col] || ((char *)df->data[i][col])[0] == '\0')
            continue;
        value = get_value(df->data[i][col], df->column_types[col]);
        update_min_max(stats, value);
        sum += value;
        sq_sum += value * value;
        stats->count++;
    }
    if (stats->count == 0)
        return;
    stats->mean = (double)sum / stats->count;
    stats->std = sqrt((sq_sum / stats->count) - (stats->mean * stats->mean));
}

void df_describe(dataframe_t *df)
{
    statistics_t stats;

    if (!df || df->nb_rows == 0)
        return;
    for (int i = 0; i < df->nb_columns; i++) {
        if (df->column_types[i] == BOOL || df->column_types[i] == STRING
            || df->column_types[i] == UNDEFINED)
            continue;
        calculate_statistics(df, i, &stats);
        printf("Column: %s\n", df->column_names[i]);
        printf("Count: %d\n", stats.count);
        printf("Mean: %.2f\n", stats.mean);
        printf("Std: %.2f\n", stats.std);
        printf("Min: %.2f\n", stats.min);
        printf("Max: %.2f\n", stats.max);
        printf("\n");
    }
}
