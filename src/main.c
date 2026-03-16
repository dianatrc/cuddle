/*
** EPITECH PROJECT, 2026
** Cuddle
** File description:
** Main entry point for the
** cuddle project.
*/

#include "dataframe.h"

int main(void)
{
    dataframe_t *df = df_read_csv("data.csv", ",");
    dataframe_t *sorted;
    dataframe_shape_t shape;

    if (!df)
        return 84;
    df_info(df);
    shape = df_shape(df);
    printf("Shape: %d rows, %d columns\n", shape.nb_rows, shape.nb_columns);
    df_describe(df);
    sorted = df_sort(df, "age", compare_int);
    df_describe(sorted);
    return 0;
}
