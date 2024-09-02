#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/dict.h"
#include "../include/csv.h"
#include "../include/search.h"
#include "../include/patricia.h"

int main(int argc, char *argv[]) {
    // printf(argv[1]);
    // if (argc != 4) {
    //     fprintf(stderr, "Usage: %s <stage> <input_csv> <output_file>\n", argv[0]);
    //     exit(EXIT_FAILURE);
    // }

    int stage = atoi(argv[1]);
    const char *input_csv = argv[2];
    const char *output_file = argv[3];

    if (stage == 1) {
        Dictionary *dict = create_dictionary();
        dict->head = load_data(input_csv);
        FILE *output = fopen(output_file, "w");
        if (!output) {
            perror("Failed to open output file");
            exit(EXIT_FAILURE);
        }
        char query[MAX_FIELD_LENGTH];
        while (fgets(query, sizeof(query), stdin)) {
            query[strcspn(query, "\n")] = '\0'; // Remove newline character
            SearchResult *results = search_suburbs(dict, query);
            print_search_results(results, output, query);
            if (!results || results->count == 0) {
                printf("%s --> NOTFOUND\n", query);
            } else {
                printf("%s --> %d records found\n", query, results->count);
            }
            free_search_results(results);
        }        
        fclose(output);
        free_dictionary(dict);
    } else if (stage == 2) {
        Dictionary *dict = create_dictionary();
        dict->head = load_data(input_csv);
        FILE *output = fopen(output_file, "w");
        if (!output) {
            perror("Failed to open output file");
            exit(EXIT_FAILURE);
        }
        char query[MAX_FIELD_LENGTH];
        while (fgets(query, sizeof(query), stdin)) {
            query[strcspn(query, "\n")] = '\0'; // Remove newline character
            int deleted = delete_suburb_records(dict, query);
            if (deleted == 0) {
                printf("%s --> NOTFOUND\n", query);
            } else {
                printf("%s --> %d records deleted\n", query, deleted);
            }
        }
        write_remaining_records(dict, output);
        fclose(output);
        free_dictionary(dict);
    } else if (stage == 4) {
        PatriciaNode *root = NULL;
        FILE *output = fopen(output_file, "w");
        if (!output) {
            perror("Failed to open output file");
            exit(EXIT_FAILURE);
        }
        loadData(input_csv, &root);
        // Accept suburb names from stdin and search the Patricia tree
        char query[MAX_FIELD_LENGTH];
        while (fgets(query, sizeof(query), stdin)) {
            query[strcspn(query, "\n")] = 0; // Remove newline character
            QueryResult *result = searchPatriciaTree(root, query);
            if (result->matchesFound > 0) {
                outputSearchResults(output, result);
                printf("%s --> %d records - comparisons: b%d n%d s%d\n", query, result->matchesFound,
                    result->bitComparisons, result->nodeAccesses, result->stringComparisons);
            } else {
                printf("%s --> NOTFOUND\n", query);
            }
        }
        fclose(output);
    } else {
        fprintf(stderr, "Invalid stage: %d\n", stage);
        exit(EXIT_FAILURE);
    }

    return 0;
}
