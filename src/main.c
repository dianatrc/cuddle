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
    dataframe_shape_t shape;
    dataframe_t *filtered;
    dataframe_t *transformed;

    if (!df)
        return 84;
    df_info(df);
    filtered = df_filter(df, "age", filter_function);
    shape = df_shape(df);
    printf("Shape: %d rows, %d columns\n", shape.nb_rows, shape.nb_columns);
    if (df_write_csv(filtered, "out") == -1)
        return 84;
    df_describe(df);
    transformed = df_apply(df, "age", multiply);
    df_write_csv(transformed, "data.out");
    df_free(df);
    df_free(filtered);
    free(transformed);
    return 0;
}
