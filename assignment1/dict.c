#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dict.h"

SuburbRecord *load_data(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    char buffer[512];
    SuburbRecord *head = NULL;
    SuburbRecord *tail = NULL;

    // Skip the header line
    if (fgets(buffer, sizeof(buffer), file) == NULL) {
        fclose(file);
        return NULL;
    }

    while (fgets(buffer, sizeof(buffer), file)) {
        SuburbRecord *new_record = (SuburbRecord *)malloc(sizeof(SuburbRecord));
        if (!new_record) {
            perror("Failed to allocate memory");
            exit(EXIT_FAILURE);
        }

        sscanf(buffer, "%d,%d,%99[^,],%d,%d,%99[^,],%99[^,],%99[^,],%lf,%lf",
               &new_record->comp20003_code,
               &new_record->official_code_suburb,
               new_record->official_name_suburb,
               &new_record->year,
               &new_record->official_code_state,
               new_record->official_name_state,
               new_record->official_code_lga,
               new_record->official_name_lga,
               &new_record->latitude,
               &new_record->longitude);
        
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

void search_suburbs(SuburbRecord *head, const char *query, FILE *output) {
    SuburbRecord *current = head;
    int found = 0;

    fprintf(output, "%s -->\n", query);

    while (current) {
        if (strcmp(current->official_name_suburb, query) == 0) {
            fprintf(output, "COMP20003 Code: %d, Official Code Suburb: %d, Official Name Suburb: %s, Year: %d, Official Code State: %d, Official Name State: %s, Official Code Local Government Area: %s, Official Name Local Government Area: %s, Latitude: %.6lf, Longitude: %.6lf\n",
                    current->comp20003_code, current->official_code_suburb, current->official_name_suburb,
                    current->year, current->official_code_state, current->official_name_state,
                    current->official_code_lga, current->official_name_lga, current->latitude, current->longitude);
            found++;
        }
        current = current->next;
    }

    if (found == 0) {
        fprintf(output, "NOTFOUND\n");
    }

    printf("%s --> %d records found\n", query, found);
}

int delete_suburb_records(SuburbRecord **head_ref, const char *suburb_name) {
    SuburbRecord *current = *head_ref;
    SuburbRecord *prev = NULL;
    int count = 0;

    while (current != NULL) {
        if (strcmp(current->official_name_suburb, suburb_name) == 0) {
            if (prev == NULL) { // Node to be deleted is head
                *head_ref = current->next;
            } else {
                prev->next = current->next;
            }
            SuburbRecord *temp = current;// need to free the delete node memory.
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

void write_remaining_records(SuburbRecord *head, FILE *output) {
    // Write the header to the output file
    fprintf(output, "COMP20003 Code,Official Code Suburb,Official Name Suburb,Year,Official Code State,Official Name State,Official Code Local Government Area,Official Name Local Government Area,Latitude,Longitude\n");
    
    SuburbRecord *current = head;
    while (current != NULL) {
        fprintf(output, "%d,%d,%s,%d,%d,%s,%s,%s,%f,%f\n",
                current->comp20003_code, current->official_code_suburb, current->official_name_suburb,
                current->year, current->official_code_state, current->official_name_state,
                current->official_code_lga, current->official_name_lga, current->latitude, current->longitude);
        current = current->next;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <stage> <input_csv> <output_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int stage = atoi(argv[1]);
    const char *input_csv = argv[2];
    const char *output_file = argv[3];

    SuburbRecord *head = load_data(input_csv);
    FILE *output = fopen(output_file, "w");
    if (!output) {
        perror("Failed to open output file");
        exit(EXIT_FAILURE);
    }

    if (stage == 1) {
        char query[MAX_FIELD_LENGTH];
        while (fgets(query, sizeof(query), stdin)) {
            query[strcspn(query, "\n")] = '\0'; // Remove newline character
            search_suburbs(head, query, output);
        }
    } else if (stage == 2) {
        int total_deleted = 0;
        char query[MAX_FIELD_LENGTH];
        while (fgets(query, sizeof(query), stdin)) {
            query[strcspn(query, "\n")] = '\0'; // Remove newline character
            int deleted = delete_suburb_records(&head, query);
            if (deleted == 0) {
                printf("%s --> NOTFOUND\n", query);
            } else {
                printf("%s --> %d records deleted\n", query, deleted);
                total_deleted += deleted;
            }
        }
        write_remaining_records(head, output);
        printf("Total records deleted: %d\n", total_deleted);
    } else {
        fprintf(stderr, "Invalid stage: %d\n", stage);
        exit(EXIT_FAILURE);
    }

    fclose(output);

    // Free the linked list
    while (head != NULL) {
        SuburbRecord *temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}