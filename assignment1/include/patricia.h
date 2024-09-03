
#ifndef PATRICIA_H
#define PATRICIA_H

#include "struct.h"

void creatPatriciaTreeFromCsv(const char *filename, PatriciaNode **root);
QueryResult *searchPatriciaTree(PatriciaNode *root, const char *suburbQuery);
PatriciaNode *insertPatriciaNode(PatriciaNode *root, char *key, SuburbRecord *record, int * bitIndex);
void freePatriciaTree(PatriciaNode *root);

#endif // PATRICIA_H