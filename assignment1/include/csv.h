#ifndef CSV_H
#define CSV_H

#include "dict.h"

SuburbRecord *load_data(const char *filename);
void write_remaining_records(Dictionary *dict, FILE *output);

#endif // CSV_H
