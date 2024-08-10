#ifndef DICT_H
#define DICT_H

#define MAX_FIELD_LENGTH 128

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

typedef struct {
    SuburbRecord *head;
} Dictionary;

Dictionary *create_dictionary();
void free_dictionary(Dictionary *dict);
void add_record(Dictionary *dict, SuburbRecord *record);
int delete_suburb_records(Dictionary *dict, const char *suburb_name);

#endif // DICT_H
