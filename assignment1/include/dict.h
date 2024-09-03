#ifndef DICT_H
#define DICT_H

#include "struct.h"

Dictionary *create_dictionary();
void free_dictionary(Dictionary *dict);
void add_record(Dictionary *dict, SuburbRecord *record);
int delete_suburb_records(Dictionary *dict, const char *suburb_name);
QueryResult *searchSuburb(SuburbRecord *head, const char *query);

#endif // DICT_H
