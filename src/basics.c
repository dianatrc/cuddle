/*
** EPITECH PROJECT, 2026
** Cuddle
** File description:
** Main entry point for the
** cuddle project.
*/

#include "dataframe.h"

static void copy_data(dataframe_t *new_df, dataframe_t *df, int i)
{
    int size;

    for (int j = 0; j < df->nb_columns; j++) {
        if (!df->data[i][j]) {
            new_df->data[i][j] = NULL;
            continue;
        }
        if (new_df->column_types[j] == STRING) {
            new_df->data[i][j] = strdup((char *)df->data[i][j]);
            continue;
        }
        if (new_df->column_types[j] == FLOAT)
            size = sizeof(float);
        else
            size = sizeof(int);
        new_df->data[i][j] = malloc(size);
        if (new_df->data[i][j])
            memcpy(new_df->data[i][j], df->data[i][j], size);
    }
}

dataframe_t *df_head(dataframe_t *df, int nb_rows)
{
    dataframe_t *new_df = create_df();

    if (!df || nb_rows <= 0 || !new_df)
        return NULL;
    if (nb_rows > df->nb_rows)
        nb_rows = df->nb_rows;
    new_df->nb_rows = nb_rows;
    new_df->nb_columns = df->nb_columns;
    new_df->column_names = malloc(sizeof(char *) * df->nb_columns);
    new_df->column_types = malloc(sizeof(column_type_t) * df->nb_columns);
    new_df->data = malloc(sizeof(void **) * nb_rows);
    for (int i = 0; i < df->nb_columns; i++) {
        new_df->column_names[i] = strdup(df->column_names[i]);
        new_df->column_types[i] = df->column_types[i];
    }
    for (int i = 0; i < nb_rows; i++) {
        new_df->data[i] = malloc(sizeof(void *) * df->nb_columns);
        copy_data(new_df, df, i);
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
