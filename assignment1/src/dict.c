#include <stdlib.h>
#include <string.h>
#include "../include/dict.h"

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
