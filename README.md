# Cuddle

Cuddle is a static library written in **C** that mimics core data manipulation and analysis features inspired by the Python `pandas` library. It provides a custom, efficient tabular data structure for reading, analyzing, transforming, and exporting CSV datasets directly within C environments.

# Key Features
The project is built around a custom `dataframe_t` structure and offers a complete set of features for working with tabular data:

**Reading and Writing (I/O):**
- df_read_csv: reads a CSV file with support for custom separators (default to comma if not specified), automatically detects rows, columns, and figures out the data type for each column (such as numbers, text, or true/false values).
- df_write_csv: saves the data back into a CSV file while keeping the correct formatting and original separator.

**Data Inspection:**
- df_head/df_tail: extracts just the first or last N rows of the table, just like in pandas.
- df_shape: gives you the size of the table (number of rows and columns).
- df_info: displays a list of all columns along with their data types.
- df_describe: automatically calculates basic statistics for numeric columns (mean, minimum, maximum, standard deviation).

**Filtering and Sorting:**
- df_filter: filters rows in the table based on a custom condition.
- df_sort: sorts rows in ascending or descending order based on values in a specific column.

**Transformations and Grouping:**
- df_groupby: groups data by a specific column and applies calculations across the remaining data.
- df_apply: modifies values in a column by running a function on each individual element.
- df_to_type: changes a column's data type (for example, converting text to numbers)
- df_join: merges two different tables together based on a shared column.

**Utilities and Data Access:**
- df_get_value: retrieves a specific cell value by row index and column name.
- df_get_values: extracts an array of values from a specified column.
- df_get_unique_values: retrieves an array of unique values within a column.

# Error Handling and Robustness
The library implements strict checks to handle erroneous inputs:
- Functions safely return `NULL` upon failure (such as invalid arguments, memory allocation errors, or unparseable formats) to prevent crashes and ensure proper memory control.
- Complies with standard error management by handling error outputs and exit codes appropriately (the program exits with the 84 error code, or 0 if there is no error).

# Project Structure
- include/
    - dataframe.h   # Main header containing structures and function prototypes
- src/              # Implementation source files (.c)
- Makefile          # Compilation rules (all, clean, fclean, re)
- README.md

# Compilation and Build
To compile the static library (libcuddle.a), use the provided Makefile:
- make: compile the static library
- make clean: clean up temporary object files
- make fclean: clean up object files and the binary library
- make re: rebuild the project from scratch