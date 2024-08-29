#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../include/patricia.h"


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
    int binaryStringLength = len * 8;
    char *binaryString = malloc(binaryStringLength + 1);  // +1 for null terminator
    if (!binaryString) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    binaryString[0] = '\0';  // Initialize as an empty string

    for (int i = 0; i < len; i++) {
        char *charBinary = charToBinary(str[i]);
        strcat(binaryString, charBinary);
        free(charBinary);
    }

    return binaryString;
}


void printStringAsBinary(const char *str) {
    printf("%s -> ", str);
    while (*str != '\0') {
        unsigned char ch = *str;
        for (int i = 7; i >= 0; i--) {
            printf("%d", (ch >> i) & 1);
        }
        // printf(" ");  // Separate binary representations with a space
        str++;
    }
    printf("\n");
}

int min(int x, int y) {
    return (x < y) ? x : y;
}

int getBit(char *s, unsigned int bitIndex) {
    assert(s && bitIndex >= 0);
    unsigned int byte = bitIndex / BITS_PER_BYTE;
    unsigned int indexFromLeft = bitIndex % BITS_PER_BYTE;
    unsigned int offset = (BITS_PER_BYTE - indexFromLeft - 1) % BITS_PER_BYTE;
    unsigned char byteOfInterest = s[byte];
    unsigned int offsetMask = 1 << offset;
    unsigned int maskedByte = byteOfInterest & offsetMask;
    unsigned int bitOnly = maskedByte >> offset;
    return bitOnly;
}

char *createStem(char *oldKey, unsigned int startBit, unsigned int numBits) {
    printf("%s, %d, %d\n", oldKey, startBit, numBits);
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

PatriciaNode *insertPatriciaNode(PatriciaNode *root, char *key, SuburbRecord *record) {
    if (!root) {
        // Create a new node with the entire key as the prefix
        PatriciaNode *newNode = malloc(sizeof(PatriciaNode));
        assert(newNode);
        newNode->prefix = createStem(key, 0, strlen(key) * BITS_PER_BYTE);
        newNode->prefixBits = strlen(key) * BITS_PER_BYTE;
        newNode->branchA = newNode->branchB = NULL;
        newNode->record = record;
        return newNode;
    }

    // Traverse the tree
    PatriciaNode *current = root;
    unsigned int bitIndex = 0;
    printf("key: %s\n", key);
    printStringAsBinary(key);
    printStringAsBinary(current->prefix);
    while (bitIndex < current->prefixBits && getBit(key, bitIndex) == getBit(current->prefix, bitIndex)) {
        bitIndex++;
    }
    printf("bitIndex: %d\n", bitIndex);
    // Mismatch found or end of the prefix
    if (bitIndex < current->prefixBits) {
        // Adjust the current node to represent the common prefix only
        PatriciaNode *splitNode = malloc(sizeof(PatriciaNode));
        assert(splitNode);

        // The common prefix is from 0 to bitIndex
        splitNode->prefix = createStem(current->prefix, 0, bitIndex);
        splitNode->prefixBits = bitIndex;

        // Now adjust the current node to represent the remainder of its original prefix
        unsigned int remainingBits = current->prefixBits - bitIndex;
        char *remainingPrefix = createStem(current->prefix, bitIndex, remainingBits);

        current->prefix = remainingPrefix;
        current->prefixBits = remainingBits;

        // Determine which branch the current node and the new node should go into
        if (getBit(key, bitIndex)) {
            splitNode->branchA = current;  // Current node goes into branchA
            splitNode->branchB = NULL;  // New node goes into branchB
        } else {
            splitNode->branchB = current;  // Current node goes into branchB
            splitNode->branchA = NULL;  // New node goes into branchA
        }

        // Create a new leaf node for the inserted key
        PatriciaNode *newLeaf = malloc(sizeof(PatriciaNode));
        assert(newLeaf);
        newLeaf->prefix = createStem(key, bitIndex, strlen(key) * BITS_PER_BYTE - bitIndex);
        newLeaf->prefixBits = strlen(key) * BITS_PER_BYTE - bitIndex;
        newLeaf->branchA = newLeaf->branchB = NULL;
        newLeaf->record = record;

        // Attach the new leaf node to the split node
        if (getBit(key, bitIndex)) {
            splitNode->branchB = newLeaf;
        } else {
            splitNode->branchA = newLeaf;
        }

        return splitNode;
    }

    // If the entire prefix matches, go deeper into the tree
    char *newKey = createStem(key, bitIndex, strlen(key) * BITS_PER_BYTE - bitIndex);
    if (bitIndex < strlen(key) * BITS_PER_BYTE) {
        if (getBit(key, bitIndex)) {
            printf("enter branchB\n");
            current->branchB = insertPatriciaNode(current->branchB, newKey, record);
        } else {
            printf("enter branchA\n");
            current->branchA = insertPatriciaNode(current->branchA, newKey, record);            
        }
    } else {
        // The key fully matches the current node's prefix, so just update the record
        current->record = record;
    }

    return root;
}

QueryResult searchPatriciaTree(PatriciaNode *root, const char *suburbQuery) {
    QueryResult result;
    result.suburbQuery = strdup(suburbQuery);
    result.matchesFound = 0;
    result.bitComparisons = 0;
    result.nodeAccesses = 0;
    result.stringComparisons = 0;
    result.matches = NULL;

    if (!root) {
        return result;  // If the tree is empty, return an empty result
    }

    PatriciaNode *current = root;
    int bitIndex = 0;
    int stringLen = strlen(suburbQuery);
    SuburbRecord *closestRecord = NULL;
    int minEditDistance = INT_MAX;
    char *queryBinary = createStem(suburbQuery, 0, strlen(suburbQuery) * BITS_PER_BYTE);
    printStringAsBinary(queryBinary);
    while (current) {
        result.nodeAccesses++;

        // Compare the current node's prefix with the corresponding part of the suburb query
        printStringAsBinary(current->prefix);
        for (int i = 0; i < current->prefixBits; i++) {
            int bitInKey = getBit(suburbQuery, bitIndex + i);
            int bitInPrefix = getBit(current->prefix, i);
            result.bitComparisons++;
            bitIndex++;

            if (bitInKey != bitInPrefix) {
                // Mismatch found, stop comparing further bits
                bitIndex += i;
                break;
            }
        }

        // bitIndex += current->prefixBits;

        // Check if we have reached a leaf node
        if (!current->branchA && !current->branchB) {
            result.stringComparisons++;
            if (strncmp(suburbQuery, current->record->official_name_suburb, stringLen) == 0) {
                printf("exact record: %s", current->record->official_name_suburb);
                // Exact match found
                result.matchesFound = 1;
                result.matches = malloc(sizeof(SuburbRecord *));
                result.matches[0] = current->record;
                return result;
            } else {
                // Mismatch found, calculate the edit distance
                printf("closestRecord: %s", current->record->official_name_suburb);
                char *remainQueryBinaries = convertStringAsBinary(createStem(suburbQuery, bitIndex, stringLen - bitIndex));
                char *remainSubNameBinaries = convertStringAsBinary(createStem(current->record->official_name_suburb, bitIndex, strlen(current->record->official_name_suburb) * BITS_PER_BYTE - bitIndex));
                int currentDistance = editDistance(remainQueryBinaries, remainSubNameBinaries, strlen(remainQueryBinaries), strlen(remainSubNameBinaries));
                if (currentDistance < minEditDistance) {
                    minEditDistance = currentDistance;
                    closestRecord = current->record;
                }
            }
        }

        // Move to the next node in the Patricia tree
        if (bitIndex < stringLen * BITS_PER_BYTE) {
            int nextBit = getBit(suburbQuery, bitIndex);
            current = nextBit ? current->branchB : current->branchA;
        } else {
            break;  // End of the query string reached
        }
    }

    // If the search reaches here, no exact match was found
    result.matchesFound = 1;
    result.matches = closestRecord;
    // printf("closestRecord: %s", closestRecord->official_name_suburb);
    return result;
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

// SuburbRecord *findClosestMatch(PatriciaNode *node,   int *minEditDistance) {
//     if (!node) return NULL;

//     // if leaf node found, we calculate the edit distance between the binary suburbName and query.
//     if (!node->branchA && node->branchB) {
//         int currentDistance = editDistance(createStem(node->record->suburbName, 0, strlen(node->record->suburbName) * BITS_PER_BYTE), createStem(query, 0, strlen(query) * BITS_PER_BYTE), strlen(node->record->suburbName) * BITS_PER_BYTE, strlen(query) * BITS_PER_BYTE);
//         if (currentDistance < *minEditDistance) {
//             *minEditDistance = currentDistance;
//         }
//     }
    

//     SuburbRecord *leftMatch = findClosestMatch(node->branchA, query, minEditDistance);
//     SuburbRecord *rightMatch = findClosestMatch(node->branchB, query, minEditDistance);

//     return (leftMatch && currentDistance == *minEditDistance) ? leftMatch : rightMatch;
// }

// void outputSearchResults(FILE *outputFp, QueryResult result) {
//     fprintf(outputFp, "COMP20003 Code,Official Code Suburb,Official Name Suburb,Year,Official Code State,Official Name State,Official Code Local Government Area,Official Name Local Government Area,Latitude,Longitude\n");

//     if (result.record) {
//         fprintf(outputFp, "%d,%d,%s,%d,%d,%s,%s,%s,%f,%f\n",
//                 current->comp20003_code, current->official_code_suburb, current->official_name_suburb,
//                 current->year, current->official_code_state, current->official_name_state,
//                 current->official_code_lga, current->official_name_lga, current->latitude, current->longitude);
//         current = current->next;
//         fprintf(outputFp, "%s --> COMP20003 Code: %d, Official Code Suburb: %d, Official Name Suburb: %s, Year: %d, Official Code State: %s\n",
//                 result.record->officialNameSuburb, result.record->comp20003Code, result.record->officialCodeSuburb,
//                 result.record->officialNameSuburb, result.record->year, result.record->officialCodeState);
//     }
// }

void freePatriciaTree(PatriciaNode *root) {
    if (root) {
        freePatriciaTree(root->branchA);
        freePatriciaTree(root->branchB);
        free(root->prefix);
        free(root);
    }
}

