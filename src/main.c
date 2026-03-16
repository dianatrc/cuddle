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
    dataframe_t *filtered;
    void **values = df_get_values(df, "age");

    if (!df)
        return 84;
    df_info(df);
    filtered = df_filter(df, "age", filter_function);
    if (df_write_csv(filtered, "out") == -1)
        return 84;
    for (int i = 0; i < df->nb_rows; i++) {
        if (values[i])
            printf("Value: %d\n", *(int *)values[i]);
        else
            printf("Value: empty\n");
    }
    df_free(df);
    df_free(filtered);
    free(values);
    return 0;
}
