
#ifndef PATRICIA_H
#define PATRICIA_H

#include "dict.h"

#define BITS_PER_BYTE 8

typedef struct PatriciaNode {
    char *prefix;                     // Binary prefix stored at this node
    int prefixBits;                   // Number of bits in the prefix
    struct PatriciaNode *branchA;     // Child node A
    struct PatriciaNode *branchB;     // Child node B
    SuburbRecord *record;             // Associated records
    int isLeafNode;
    int isDummyNode;
} PatriciaNode;

typedef struct {
    char *suburbQuery;         // The suburb name queried
    int matchesFound;          // Number of matching records found
    int bitComparisons;        // Number of bit comparisons made during the search
    int nodeAccesses;          // Number of nodes accessed during the search
    int stringComparisons;     // Number of string comparisons made
    SuburbRecord *matches;    // Pointer to the array of matching records
} QueryResult;


void loadData(const char *filename, PatriciaNode **root);
QueryResult *searchPatriciaTree(PatriciaNode *root, const char *suburbQuery);
PatriciaNode *insertPatriciaNode(PatriciaNode *root, char *key, SuburbRecord *record, int * bitIndex);
void outputSearchResults(FILE *outputFp, QueryResult *result);
void freePatriciaTree(PatriciaNode *root);

#endif // PATRICIA_H