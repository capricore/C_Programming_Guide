#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dict.h"
#include "csv.h"
#include "search.h"

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <stage> <input_csv> <output_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int stage = atoi(argv[1]);
    const char *input_csv = argv[2];
    const char *output_file = argv[3];

    Dictionary *dict = create_dictionary();
    dict->head = load_data(input_csv);
    FILE *output = fopen(output_file, "w");
    if (!output) {
        perror("Failed to open output file");
        exit(EXIT_FAILURE);
    }

    if (stage == 1) {
        char query[MAX_FIELD_LENGTH];
        while (fgets(query, sizeof(query), stdin)) {
            query[strcspn(query, "\n")] = '\0'; // Remove newline character
            SearchResult *results = search_suburbs(dict, query);
            print_search_results(results, output);
            free_search_results(results);
        }
    } else if (stage == 2) {
        int total_deleted = 0;
        char query[MAX_FIELD_LENGTH];
        while (fgets(query, sizeof(query), stdin)) {
            query[strcspn(query, "\n")] = '\0'; // Remove newline character
            int deleted = delete_suburb_records(dict, query);
            if (deleted == 0) {
                printf("%s --> NOTFOUND\n", query);
            } else {
                printf("%s --> %d records deleted\n", query, deleted);
                total_deleted += deleted;
            }
        }
        write_remaining_records(dict, output);
        printf("Total records deleted: %d\n", total_deleted);
    } else {
        fprintf(stderr, "Invalid stage: %d\n", stage);
        exit(EXIT_FAILURE);
    }

    fclose(output);
    free_dictionary(dict);
    return 0;
}