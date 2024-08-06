#ifndef DICT_H
#define DICT_H

#define MAX_FIELD_LENGTH 127

typedef struct SuburbRecord {
    int comp20003_code;
    int official_code_suburb;
    char official_name_suburb[MAX_FIELD_LENGTH];
    int year;
    int official_code_state;
    char official_name_state[MAX_FIELD_LENGTH];
    char official_code_lga[MAX_FIELD_LENGTH];
    char official_name_lga[MAX_FIELD_LENGTH];
    double latitude;
    double longitude;
    struct SuburbRecord *next;
} SuburbRecord;
SuburbRecord *load_data(const char *filename);
void search_suburbs(SuburbRecord *head, const char *query, FILE *output);
#endif // DICT_H