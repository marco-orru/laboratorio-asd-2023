#include <stdlib.h>
#include "file-sorter.h"

#define SORT_FIELD FIELD_INTEGER

int main() {
    FILE *in_file, *out_file;

    in_file = fopen("resources/records.csv", "r");

    if (!in_file) {
        fprintf(stderr, "Error: Failed to open 'records.csv' file");
        exit(EXIT_FAILURE);
    }

    out_file = fopen("resources/sorted.txt", "w");

    if (!out_file) {
        fclose(in_file);

        fprintf(stderr, "Error: Failed to open 'sorted.txt' file");
        exit(EXIT_FAILURE);
    }

    sort_records(in_file, out_file, 20, SORT_FIELD);

    fclose(in_file);
    fclose(out_file);

    return EXIT_SUCCESS;
}