#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "search.h"

SearchResult *search_suburbs(Dictionary *dict, const char *query) {
    SuburbRecord *current = dict->head;
    SearchResult *results = malloc(sizeof(SearchResult));
    if (!results) {
        perror("Failed to allocate memory for SearchResult");
        exit(EXIT_FAILURE);
    }
    results->records = NULL;
    results->count = 0;

    while (current) {
        if (strcmp(current->official_name_suburb, query) == 0) {
            SuburbRecord *record_copy = malloc(sizeof(SuburbRecord));
            if (!record_copy) {
                perror("Failed to allocate memory for SuburbRecord");
                exit(EXIT_FAILURE);
            }
            *record_copy = *current; // Perform a shallow copy of the SuburbRecord data
            record_copy->next = NULL;

            // Insert the record at the beginning of the list
            record_copy->next = results->records;
            results->records = record_copy;

            results->count++;
        }
        current = current->next;
    }

    return results;
}

void print_search_results(SearchResult *results, FILE *output, const char *query) {
    // Print the query header
    fprintf(output, "%s -->\n", query);

    // Check if there are any results
    if (!results || results->count == 0) {
        fprintf(output, "NOTFOUND\n");
        return;
    }

    // Iterate through the linked list of SuburbRecords
    SuburbRecord *record = results->records; // Start with the head of the linked list
    while (record) {
        fprintf(output, "COMP20003 Code: %d, Official Code Suburb: %d, Official Name Suburb: %s, Year: %d, Official Code State: %d, Official Name State: %s, Official Code Local Government Area: %s, Official Name Local Government Area: %s, Latitude: %lf, Longitude: %lf\n",
                record->comp20003_code, record->official_code_suburb, record->official_name_suburb,
                record->year, record->official_code_state, record->official_name_state,
                record->official_code_lga, record->official_name_lga, record->latitude, record->longitude);
        record = record->next; // Move to the next SuburbRecord in the list
    }
}

void free_search_results(SearchResult *results) {
    if (results) {
        SuburbRecord *current = results->records;
        while (current) {
            SuburbRecord *next = current->next; // Store the next node
            free(current); // Free the current node
            current = next; // Move to the next node
        }
        free(results); // Free the SearchResult structure itself
    }
}

