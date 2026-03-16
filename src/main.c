/*
** EPITECH PROJECT, 2026
** Cuddle - Bootstrap
** File description:
** Main entry point for the
** cuddle bootstrap.
*/

#include "../include/dataframe.h"

int main(void)
{
    dataframe_t *df;
    dataframe_shape_t shape;
    dataframe_t *filtered;

    df = df_read_csv("utils/data.csv", ",");
    if (!df)
        return 84;
    df_info(df);
    filtered = df_filter(df, "age", filter_function);
    shape = df_shape(df);
    printf("Shape: %d rows, %d columns\n", shape.nb_rows, shape.nb_columns);
    if (df_write_csv(filtered, "out") == -1)
        return 84;
    df_describe(df);
    free_df(df);
    free_df(filtered);
    return 0;
}
