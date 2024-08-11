#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "search.h"

SearchResult *search_suburbs(Dictionary *dict, const char *query) {
    SuburbRecord *current = dict->head;
    SearchResult *results = NULL;
    SearchResult *last_result = NULL;

    while (current) {
        if (strcmp(current->official_name_suburb, query) == 0) {
            SearchResult *new_result = malloc(sizeof(SearchResult));
            new_result->record = current;
            new_result->next = NULL;

            if (last_result) {
                last_result->next = new_result;
            } else {
                results = new_result;
            }
            last_result = new_result;
        }
        current = current->next;
    }

    return results;
}

int print_search_results(SearchResult *results, FILE *output) {
    int count = 0;
    while (results) {
        SuburbRecord *record = results->record;
        fprintf(output, "COMP20003 Code: %d, Official Code Suburb: %d, Official Name Suburb: %s, Year: %d, Official Code State: %d, Official Name State: %s, Official Code Local Government Area: %s, Official Name Local Government Area: %s, Latitude: %.6lf, Longitude: %.6lf\n",
                record->comp20003_code, record->official_code_suburb, record->official_name_suburb,
                record->year, record->official_code_state, record->official_name_state,
                record->official_code_lga, record->official_name_lga, record->latitude, record->longitude);
        results = results->next;
        count++;
    }
    return count;
}

void free_search_results(SearchResult *results) {
    while (results) {
        SearchResult *temp = results;
        results = results->next;
        free(temp);
    }
}
