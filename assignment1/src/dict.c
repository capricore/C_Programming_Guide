#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "../include/dict.h"
#include "../include/struct.h"

Dictionary *create_dictionary() {
    Dictionary *dict = (Dictionary *)malloc(sizeof(Dictionary));
    if (!dict) {
        perror("Failed to allocate memory for dictionary");
        exit(EXIT_FAILURE);
    }
    dict->head = NULL;
    return dict;
}

void free_dictionary(Dictionary *dict) {
    SuburbRecord *current = dict->head;
    while (current != NULL) {
        SuburbRecord *temp = current;
        current = current->next;
        free(temp);
    }
    free(dict);
}

void add_record(Dictionary *dict, SuburbRecord *record) {
    record->next = dict->head;
    dict->head = record;
}

int delete_suburb_records(Dictionary *dict, const char *suburb_name) {
    SuburbRecord *current = dict->head;
    SuburbRecord *prev = NULL;
    int count = 0;

    while (current != NULL) {
        if (strcmp(current->official_name_suburb, suburb_name) == 0) {
            if (prev == NULL) {
                dict->head = current->next;
            } else {
                prev->next = current->next;
            }
            SuburbRecord *temp = current;
            current = current->next;
            free(temp);
            count++;
        } else {
            prev = current;
            current = current->next;
        }
    }
    return count;
}

QueryResult *searchSuburb(SuburbRecord *head, const char *query) {
    QueryResult *result = malloc(sizeof(QueryResult));
    result->suburbQuery = strdup(query);
    result->matchesFound = 0;
    result->bitComparisons = 0;
    result->nodeAccesses = 0;
    result->stringComparisons = 0;
    result->matches = NULL;

    SuburbRecord *current = head;
    SuburbRecord *matchesTail = NULL;

    int queryLen = strlen(query);

    while (current) {
        result->nodeAccesses++;
        result->stringComparisons++;

        int bitComparisons = 0;
        int isMatch = 1; // Assume match until proven otherwise        
        
        // Compare each character of the suburb name
        for (int i = 0; i < strlen(query)+1 && i < strlen(current->official_name_suburb)+1; i++) {
            bitComparisons += 8; // Each character comparison adds 8 bits
            if (query[i] != current->official_name_suburb[i]) {
                isMatch = 0;
                break;
            }
        }

        result->bitComparisons += bitComparisons;

        // If it's a match, add the record to the result's matches linked list
        if (isMatch) {
            SuburbRecord *matchedRecord = malloc(sizeof(SuburbRecord));
            if (!matchedRecord) {
                perror("Failed to allocate memory");
                exit(EXIT_FAILURE);
            }
            *matchedRecord = *current;
            matchedRecord->next = NULL;
            insertSuburbRecordSorted(&(result->matches), matchedRecord);
            result->matchesFound++;
        }

        current = current->next;
    }

    return result;
}


