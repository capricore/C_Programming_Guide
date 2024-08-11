#ifndef SEARCH_H
#define SEARCH_H

#include "dict.h"

typedef struct SearchResult {
    SuburbRecord *record;
    struct SearchResult *next;
} SearchResult;

SearchResult *search_suburbs(Dictionary *dict, const char *query);
void print_search_results(SearchResult *results, FILE *output);
void free_search_results(SearchResult *results);

#endif // SEARCH_H
