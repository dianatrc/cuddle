/*
** EPITECH PROJECT, 2026
** Cuddle
** File description:
** Main entry point for the
** cuddle project.
*/

#include "dataframe.h"

static void test_get_values(dataframe_t *df, void **values)
{
    for (int i = 0; i < df->nb_rows; i++) {
        if (values[i])
            printf("Value: %d\n", *(int *)values[i]);
        else
            printf("Value: empty\n");
    }
}

int main(void)
{
    dataframe_t *df = df_read_csv("data.csv", ",");
    dataframe_t *filtered = df_filter(df, "age", filter_function);
    dataframe_t *sorted = df_sort(df, "age", compare_int);
    dataframe_t *transformed = df_apply(df, "age", multiply);
    void **values = df_get_values(df, "age");

    if (!df)
        return 84;
    df_info(df);
    df_write_csv(filtered, "filtered.out");
    df_write_csv(sorted, "sorted.out");
    df_write_csv(transformed, "transformed.out");
    test_get_values(df, values);
    df_free(filtered);
    df_free(sorted);
    df_free(transformed);
    free(values);
    df_free(df);
    return 0;
}
