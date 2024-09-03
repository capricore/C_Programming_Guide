#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../include/patricia.h"
#include "../include/struct.h"

int min(int x, int y) {
    return (x < y) ? x : y;
}

int editDistance(char *str1, char *str2, int n, int m) {
    int dp[n + 1][m + 1];
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (i == 0) {
                dp[i][j] = j;
            } else if (j == 0) {
                dp[i][j] = i;
                
            } else if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = 1 + min(dp[i - 1][j], min(dp[i][j - 1], dp[i - 1][j - 1]));
            }
        }
    }
    return dp[n][m];
}

char *setFirstNBitsToZero(char *value, int n) {
    assert(value != NULL && n >= 0);

    // Calculate the number of full bytes and remaining bits to set to zero
    int fullBytes = n / BITS_PER_BYTE;
    int remainingBits = n % BITS_PER_BYTE;

    // Create a copy of the input string to avoid modifying the original
    char *result = strdup(value);
    assert(result);

    // Set the first `fullBytes` bytes to 0
    for (int i = 0; i < fullBytes; i++) {
        result[i] = 0x00;
    }

    // Handle the remaining bits in the next byte, if any
    if (remainingBits > 0) {
        unsigned char mask = (1 << (BITS_PER_BYTE - remainingBits)) - 1;
        result[fullBytes] &= mask;
    }

    return result;
}

// Function to convert a single character to a binary string
char *charToBinary(char c) {
    char *binary = malloc(9);  // 8 bits + null terminator
    if (!binary) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    binary[8] = '\0';  // Null-terminate the string

    for (int i = 7; i >= 0; i--) {
        binary[i] = (c & 1) ? '1' : '0';
        c >>= 1;
    }

    return binary;
}

// Function to convert the entire string to its binary representation
char *convertStringAsBinary(char *str) {
    int len = strlen(str);
    int binaryStringLength = (len+1) * 8;
    char *binaryString = malloc(binaryStringLength + 1);  // +1 for null terminator
    if (!binaryString) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    binaryString[0] = '\0';  // Initialize as an empty string

    for (int i = 0; i < len+1; i++) {
        char *charBinary = charToBinary(str[i]);
        strcat(binaryString, charBinary);
        free(charBinary);
    }

    return binaryString;
}

char *createStem(char *oldKey, unsigned int startBit, unsigned int numBits) {
    assert(numBits > 0 && startBit >= 0 && oldKey);

    int extraBytes = 0;
    if ((numBits % BITS_PER_BYTE) > 0) {
        extraBytes = 1;
    }

    int totalBytes = (numBits / BITS_PER_BYTE) + extraBytes;
    char *newStem = malloc(sizeof(char) * (totalBytes + 1));
    assert(newStem);

    for (unsigned int i = 0; i < totalBytes; i++) {
        newStem[i] = 0;
    }

    for (unsigned int i = 0; i < numBits; i++) {
        unsigned int indexFromLeft = i % BITS_PER_BYTE;
        unsigned int offset = (BITS_PER_BYTE - indexFromLeft - 1) % BITS_PER_BYTE;
        unsigned int bitMaskForPosition = 1 << offset;
        unsigned int bitValueAtPosition = getBit(oldKey, startBit + i);
        unsigned int byteInNewStem = i / BITS_PER_BYTE;
        newStem[byteInNewStem] |= bitMaskForPosition * bitValueAtPosition;
    }
    // Null-terminate the new stem
    newStem[totalBytes] = '\0';
    return newStem;
}

// Function to load data from the CSV file and insert into the Patricia tree
void creatPatriciaTreeFromCsv(const char *filename, PatriciaNode **root) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    char buffer[MAX_RECORD_LENGTH];
    fgets(buffer, sizeof(buffer), file); // Skip the header line

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
        strncpy(new_record->isoCode, parse_field(&line), MAX_FIELD_LENGTH - 1);
        strncpy(new_record->type, parse_field(&line), MAX_FIELD_LENGTH - 1);
        new_record->latitude = atof(parse_field(&line));
        new_record->longitude = atof(parse_field(&line));
        new_record->next = NULL;

        // Insert the record into the Patricia tree
        int bitIndex = 0;
        *root = insertPatriciaNode(*root, new_record->official_name_suburb, new_record, &bitIndex);
    }

    fclose(file);
}

PatriciaNode *insertPatriciaNode(PatriciaNode *root, char *key, SuburbRecord *record, int *bitKeyIndex) {
    if (!root) {
        // Create a new node with the entire key as the prefix
        PatriciaNode *newNode = malloc(sizeof(PatriciaNode));
        assert(newNode);
        newNode->prefix = createStem(key, 0, strlen(key) * BITS_PER_BYTE);
        newNode->prefixBits = strlen(key) * BITS_PER_BYTE + 8;
        newNode->branchA = newNode->branchB = NULL;
        newNode->record = record;
        return newNode;
    }

    // Traverse the tree
    PatriciaNode *current = root;
    unsigned int bitIndex = 0;
    while (bitIndex < current->prefixBits && getBit(key, *bitKeyIndex) == getBit(current->prefix, bitIndex)) {
        bitIndex++;
        *bitKeyIndex += 1;
    }
    // Mismatch found inside current node prefix
    if (bitIndex < current->prefixBits) {
        // Adjust the current node to represent the common prefix only
        PatriciaNode *splitNode = malloc(sizeof(PatriciaNode));
        assert(splitNode);

        // The common prefix is from 0 to bitIndex
        splitNode->prefix = createStem(current->prefix, 0, bitIndex);
        splitNode->prefixBits = bitIndex;
        splitNode->record = current->record;

        // Now adjust the current node to represent the remainder of its original prefix
        unsigned int remainingBits = current->prefixBits - bitIndex;
        char *remainingPrefix = createStem(current->prefix, bitIndex, remainingBits);

        current->prefix = remainingPrefix;
        current->prefixBits = remainingBits;
        // Determine which branch the current node and the new node should go into
        if (getBit(key, *bitKeyIndex)) {
            splitNode->branchA = current;  // Current node goes into branchA
            splitNode->branchB = NULL;  // New node goes into branchB
        } else {
            splitNode->branchB = current;  // Current node goes into branchB
            splitNode->branchA = NULL;  // New node goes into branchA
        }

        // Create a new leaf node for the inserted key
        PatriciaNode *newLeaf = malloc(sizeof(PatriciaNode));
        assert(newLeaf);
        if (*bitKeyIndex > strlen(key) * BITS_PER_BYTE) {
            // insert dummy node
            char value[] = {0xFF};
            newLeaf->prefix = setFirstNBitsToZero(value, strlen(key) * BITS_PER_BYTE - *bitKeyIndex + 8);
            newLeaf->prefixBits = strlen(key) * BITS_PER_BYTE - *bitKeyIndex + 8;
        } else {
            newLeaf->prefix = createStem(key, *bitKeyIndex, strlen(key) * BITS_PER_BYTE - *bitKeyIndex);
            newLeaf->prefixBits = strlen(key) * BITS_PER_BYTE - *bitKeyIndex + 8;
        }
        newLeaf->branchA = newLeaf->branchB = NULL;
        newLeaf->record = record;
        // Attach the new leaf node to the split node
        if (getBit(key, *bitKeyIndex)) {
            splitNode->branchB = newLeaf;
        } else {
            splitNode->branchA = newLeaf;
        }
        return splitNode;
    }

    // If the entire prefix matches, go deeper into the tree
    if (*bitKeyIndex < strlen(key) * BITS_PER_BYTE + 8) {
        if (getBit(key, *bitKeyIndex)) {
            current->branchB = insertPatriciaNode(current->branchB, key, record, bitKeyIndex);
        } else {
            current->branchA = insertPatriciaNode(current->branchA, key, record, bitKeyIndex);            
        }
    } else {
        insertSuburbRecordSorted(&(current->record), record);
    }

    return root;
}

void find_closet_record(PatriciaNode *current, SuburbRecord** closestRecord, const char *suburbQuery, int *minEditDistance) {
    if (!current) {
        return;
    }
    if (!current->branchA && !current->branchB) {
        char *queryBinaries = convertStringAsBinary(suburbQuery);
        char *subNameBinaries = convertStringAsBinary(current->record->official_name_suburb); 
        int currentDistance = editDistance(queryBinaries, subNameBinaries, strlen(queryBinaries), strlen(subNameBinaries));
        if (*closestRecord == NULL) {
            *closestRecord = current->record;
        }
        if (currentDistance < *minEditDistance || 
            currentDistance == *minEditDistance &&
            strcmp(current->record->official_name_suburb, (*closestRecord)->official_name_suburb) < 0) {
            *minEditDistance = currentDistance;
            *closestRecord = current->record;
        }
        return;
    }
    if (current->branchA) {
        find_closet_record(current->branchA, closestRecord, suburbQuery, minEditDistance);
    }
    if (current->branchB) {
        find_closet_record(current->branchB, closestRecord, suburbQuery, minEditDistance);
    }
}

QueryResult *searchPatriciaTree(PatriciaNode *root, const char *suburbQuery) {
    QueryResult *result = malloc(sizeof(QueryResult));
    result->suburbQuery = strdup(suburbQuery);
    result->matchesFound = 0;
    result->bitComparisons = 0;
    result->nodeAccesses = 0;
    result->stringComparisons = 0;
    result->matches = NULL;

    if (!root) {
        return result;  // If the tree is empty, return an empty result
    }

    PatriciaNode *current = root;
    int bitIndex = 0;
    int stringLen = strlen(suburbQuery);
    SuburbRecord *closestRecord = NULL;
    int minEditDistance = INT_MAX;
    int mismatched = 0;
    while (current) {
        result->nodeAccesses++;
        // Compare the current node's prefix with the corresponding part of the suburb query
        for (int i = 0; i < current->prefixBits; i++) {
            int bitInKey = getBit(suburbQuery, bitIndex);
            int bitInPrefix = getBit(current->prefix, i);
            result->bitComparisons++;
            bitIndex++;
            if (bitInKey != bitInPrefix) {
                mismatched = 1;
                break;
            }
        }
        if (mismatched) {
            break;
        }
        // Move to the next node in the Patricia tree
        if (bitIndex < stringLen * BITS_PER_BYTE) {
            int nextBit = getBit(suburbQuery, bitIndex);
            current = nextBit ? current->branchB : current->branchA;
        } else  if (bitIndex > stringLen * BITS_PER_BYTE) {
            if (bitIndex == stringLen * BITS_PER_BYTE + 8) {
                result->stringComparisons++;
                break;  // End of the query string reached
            }            
            if (bitIndex < stringLen * BITS_PER_BYTE + 8) {
                if (strcmp(current->record->official_name_suburb, suburbQuery) != 0) {
                    mismatched = 1;
                    break;
                }                
                current = current->branchA;
                result->stringComparisons++;          
                break;  // End of the query string reached
            } else {
                mismatched = 1;
                break;
            }
        }
    }
    if (mismatched) {
        find_closet_record(current, &closestRecord, suburbQuery, &minEditDistance);
        result->matches = closestRecord;
        result->stringComparisons++;
        result->matchesFound = 1;
    }
    else {
        // Exact match found
        result->matches = current->record;
        result->matchesFound = 1;
    }

    return result;
}

void freePatriciaTree(PatriciaNode *root) {
    if (root == NULL) {
        return;
    }

    // Recursively free the left and right branches
    if (root->branchA) {
        freePatriciaTree(root->branchA);
    }
    if (root->branchB) {
        freePatriciaTree(root->branchB);
    }

    // Free the prefix string
    if (root->prefix) {
        free(root->prefix);
    }

    // Free the associated records linked list
    SuburbRecord *current = root->record;
    while (current != NULL) {
        SuburbRecord *nextRecord = current->next;
        
        // Avoid double-free by setting pointers to NULL after freeing
        free(current);
        current = nextRecord;
    }

    // Free the node itself
    free(root);
}
