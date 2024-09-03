#ifndef RESULT_H
#define RESULT_H

#define MAX_FIELD_LENGTH 128
#define BITS_PER_BYTE 8
#define MAX_RECORD_LENGTH 511

typedef struct SuburbRecord {
    int comp20003_code;
    int official_code_suburb;
    char official_name_suburb[MAX_FIELD_LENGTH];
    int year;
    int official_code_state;
    char official_name_state[MAX_FIELD_LENGTH];
    char official_code_lga[MAX_FIELD_LENGTH];
    char official_name_lga[MAX_FIELD_LENGTH];
    char isoCode[MAX_FIELD_LENGTH];
    char type[MAX_FIELD_LENGTH];
    double latitude;
    double longitude;
    struct SuburbRecord *next;
} SuburbRecord;

typedef struct {
    SuburbRecord *head;
} Dictionary;

typedef struct PatriciaNode {
    char *prefix;                     // Binary prefix stored at this node
    int prefixBits;                   // Number of bits in the prefix
    struct PatriciaNode *branchA;     // Child node A
    struct PatriciaNode *branchB;     // Child node B
    SuburbRecord *record;             // Associated records
} PatriciaNode;

typedef struct {
    char *suburbQuery;         // The suburb name queried
    int matchesFound;          // Number of matching records found
    int bitComparisons;        // Number of bit comparisons made during the search
    int nodeAccesses;          // Number of nodes accessed during the search
    int stringComparisons;     // Number of string comparisons made
    SuburbRecord *matches;    // Pointer to the array of matching records
} QueryResult;

typedef struct SearchResult {
    SuburbRecord *record;
    int count;
} SearchResult;

int getBit(char *s, unsigned int bitIndex);
void insertSuburbRecordSorted(SuburbRecord **head, SuburbRecord *newRecord);
void outputSearchResults(FILE *outputFp, QueryResult *result);

#endif // RESULT_H