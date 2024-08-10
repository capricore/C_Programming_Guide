#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "csv.h"

#define MAX_RECORD_LENGTH 511

char *parse_field(char **line) {
    char *field = malloc(MAX_FIELD_LENGTH * sizeof(char));
    if (**line == '"') { // indicating the start of a quoted field.
        (*line)++; // Moves the pointer past the starting double quote.
        char *start = field; // Saves the start of the buffer.
        while (**line != '"' && **line != '\0') {
            *field++ = *(*line)++;
        }
        *field = '\0';
        if (**line == '"') (*line)++;
    } else { // Handles the case where the field is not quoted.
        char *start = field;
        while (**line != ',' && **line != '\0') {
            *field++ = *(*line)++;
        }
        *field = '\0';
    }
    if (**line == ',') (*line)++;
    return start;
}

SuburbRecord *load_data(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    char buffer[MAX_RECORD_LENGTH];
    SuburbRecord *head = NULL;
    SuburbRecord *tail = NULL;

    if (fgets(buffer, sizeof(buffer), file) == NULL) {
        fclose(file);
        return NULL;
    }

    while (fgets(buffer, sizeof(buffer), file)) {
        SuburbRecord *new_record = malloc(sizeof(SuburbRecord));
        if (!new_record) {
            perror("Failed to allocate memory");
            exit(EXIT_FAILURE);
        }

        char *line = buffer;
        new_record->comp20003_code = atoi(parse_field(&line)); // int atoi(const char *str); used to convert a string to an integer
        new_record->official_code_suburb = atoi(parse_field(&line));
        strncpy(new_record->official_name_suburb, parse_field(&line), MAX_FIELD_LENGTH - 1);
        new_record->year = atoi(parse_field(&line));
        new_record->official_code_state = atoi(parse_field(&line));
        strncpy(new_record->official_name_state, parse_field(&line), MAX_FIELD_LENGTH - 1);
        strncpy(new_record->official_code_lga, parse_field(&line), MAX_FIELD_LENGTH - 1);
        strncpy(new_record->official_name_lga, parse_field(&line), MAX_FIELD_LENGTH - 1);
        new_record->latitude = atof(parse_field(&line));
        new_record->longitude = atof(parse_field(&line));
        
        new_record->next = NULL;

        if (tail) {
            tail->next = new_record;
            tail = new_record;
        } else {
            head = tail = new_record;
        }
    }

    fclose(file);
    return head;
}

void write_remaining_records(Dictionary *dict, FILE *output) {
    fprintf(output, "COMP20003 Code,Official Code Suburb,Official Name Suburb,Year,Official Code State,Official Name State,Official Code Local Government Area,Official Name Local Government Area,Latitude,Longitude\n");

    SuburbRecord *current = dict->head;
    while (current != NULL) {
        fprintf(output, "%d,%d,%s,%d,%d,%s,%s,%s,%f,%f\n",
                current->comp20003_code, current->official_code_suburb, current->official_name_suburb,
                current->year, current->official_code_state, current->official_name_state,
                current->official_code_lga, current->official_name_lga, current->latitude, current->longitude);
        current = current->next;
    }
}
