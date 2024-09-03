#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../include/patricia.h"

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
    // printf("startBit: %d,numBits: %d\n", startBit,numBits);
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
    // printf("sucess startBit: %d,numBits: %d\n", startBit,numBits);
    return newStem;
}

void insertSuburbRecordSorted(SuburbRecord **head, SuburbRecord *newRecord) {
    // If the list is empty or the new record should be at the head
    if (*head == NULL || (*head)->comp20003_code >= newRecord->comp20003_code) {
        newRecord->next = *head;
        *head = newRecord;
        return;
    }

    // Traverse the list to find the correct insertion point
    SuburbRecord *current = *head;
    while (current->next != NULL && current->next->comp20003_code < newRecord->comp20003_code) {
        current = current->next;
    }

    // Insert the new record into the list
    newRecord->next = current->next;
    current->next = newRecord;
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
        newNode->isLeafNode = 1;
        newNode->isDummyNode = 0;
        return newNode;
    }

    // Traverse the tree
    PatriciaNode *current = root;
    unsigned int bitIndex = 0;
    // printf("key: %s\n", key);
    while (bitIndex < current->prefixBits && getBit(key, *bitKeyIndex) == getBit(current->prefix, bitIndex)) {
        bitIndex++;
        *bitKeyIndex += 1;
    }
    // printf("bitIndex: %d, bitKeyIndex: %d, current->prefixBits:%d\n", bitIndex, *bitKeyIndex, current->prefixBits);
    // Mismatch found inside current node prefix
    if (bitIndex < current->prefixBits) {
        // Adjust the current node to represent the common prefix only
        PatriciaNode *splitNode = malloc(sizeof(PatriciaNode));
        assert(splitNode);

        // The common prefix is from 0 to bitIndex
        splitNode->prefix = createStem(current->prefix, 0, bitIndex);
        splitNode->prefixBits = bitIndex;
        splitNode->record = current->record;
        splitNode->isLeafNode = 0;
        splitNode->isDummyNode = 0;

        // Now adjust the current node to represent the remainder of its original prefix
        unsigned int remainingBits = current->prefixBits - bitIndex;
        char *remainingPrefix = createStem(current->prefix, bitIndex, remainingBits);

        // if (*bitKeyIndex > strlen(current->record->official_name_suburb) * BITS_PER_BYTE) {
        //     // if the inserting node is longer then current node, we need to mark current node as the end dummy node.
        //     char value[] = {0xFF};
        //     current->prefix = setFirstNBitsToZero(value, strlen(key) * BITS_PER_BYTE - *bitKeyIndex + 8);
        //     current->prefixBits = strlen(key) * BITS_PER_BYTE - *bitKeyIndex + 8;
        //     current->isDummyNode = 1;
        // } else {
        //     current->prefix = remainingPrefix;
        //     current->prefixBits = remainingBits;
        // }
        current->prefix = remainingPrefix;
        current->prefixBits = remainingBits;
        // Determine which branch the current node and the new node should go into
        // printf("before append current node: %d\n", getBit(key, *bitKeyIndex));
        if (getBit(key, *bitKeyIndex)) {
            // printf("current node prefixBit: %d\n", current->prefixBits);
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
            // printf("create dummy node: prefixBits: %d\n", newLeaf->prefixBits);
            newLeaf->isDummyNode = 1;
        } else {
            newLeaf->prefix = createStem(key, *bitKeyIndex, strlen(key) * BITS_PER_BYTE - *bitKeyIndex);
            newLeaf->prefixBits = strlen(key) * BITS_PER_BYTE - *bitKeyIndex + 8;
            // printf("create leaf node: prefixBits: %d\n", newLeaf->prefixBits);
            newLeaf->isDummyNode = 0;
        }
        newLeaf->branchA = newLeaf->branchB = NULL;
        newLeaf->record = record;
        newLeaf->isLeafNode = 1;
        // Attach the new leaf node to the split node
        // printf("before append new leaf node: %d\n", getBit(key, *bitKeyIndex));
        if (getBit(key, *bitKeyIndex)) {
            // printf("append barnchB\n");
            splitNode->branchB = newLeaf;
        } else {
            // printf("append barnchA\n");
            splitNode->branchA = newLeaf;
        }
        // printf("splitNode barnchA prefixBit: %d\n", splitNode->branchA->prefixBits);
        // printf("splitNode barnchB prefixBit: %d\n", splitNode->branchB->prefixBits);
        return splitNode;
    }

    // If the entire prefix matches, go deeper into the tree
    if (*bitKeyIndex < strlen(key) * BITS_PER_BYTE + 8) {
        // printf("nextbit: %d\n", getBit(key, *bitKeyIndex));
        if (getBit(key, *bitKeyIndex)) {
            // printf("enter barnchB\n");
            current->branchB = insertPatriciaNode(current->branchB, key, record, bitKeyIndex);
        } else {
            current->branchA = insertPatriciaNode(current->branchA, key, record, bitKeyIndex);            
        }
    } else {
        // printf("insertSuburbRecordSorted: %s\n", record->official_name_suburb);
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
        // printf("suburbQuery: %s, official_name_suburb: %s\n", suburbQuery, current->record->official_name_suburb);
        // printf("queryBinaries: %s, subNameBinaries: %s\n", queryBinaries, subNameBinaries);
        int currentDistance = editDistance(queryBinaries, subNameBinaries, strlen(queryBinaries), strlen(subNameBinaries));
        if (*closestRecord == NULL) {
            *closestRecord = current->record;
        }
        // printf("currentDistance: %d, minEditDistance: %d\n", currentDistance, *minEditDistance);
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
        // printf("current record:%s\n", current->record->official_name_suburb);
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
        // printf("bitIndex: %d, current->prefixBits:%d\n", bitIndex, current->prefixBits);
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
                // printf("current branchA: %d, %d\n", current->branchA->isLeafNode, current->branchA->isDummyNode);
                // printf("current branchB: %d, %d\n", current->branchB->isLeafNode, current->branchB->isDummyNode);

                if (strcmp(current->record->official_name_suburb, suburbQuery) != 0) {
                    mismatched = 1;
                    break;
                }                
                current = current->branchA;
                result->stringComparisons++;          
                break;  // End of the query string reached
            } else {
                // printf("current record:%s, %d, %d\n", current->record->official_name_suburb, current->isLeafNode, current->isDummyNode);
                mismatched = 1;
                break;
            }
        }
    }
    if (mismatched) {
        // printf("branch A B prefixBits: %d, %d\n", current->branchA->prefixBits, current->branchB->prefixBits);
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



void outputSearchResults(FILE *outputFp, QueryResult *result) {
    // Check if there are matching records
    int count = 0;
    if (result->matchesFound > 0) {
        SuburbRecord *current = result->matches;
        
        // Loop through the linked list of matching records
        fprintf(outputFp, "%s -->\n", result->suburbQuery);
        while (current) {     
            count++;       
            fprintf(outputFp, "COMP20003 Code: %d, Official Code Suburb: %d, Official Name Suburb: %s, Year: %d, Official Code State: %d, Official Name State: %s, Official Code Local Government Area: %s, Official Name Local Government Area: %s, Latitude: %.7lf, Longitude: %.7lf\n",
                current->comp20003_code, current->official_code_suburb, current->official_name_suburb,
                current->year, current->official_code_state, current->official_name_state,
                current->official_code_lga, current->official_name_lga, current->latitude, current->longitude);
            // Move to the next record in the list
            current = current->next;
        }
    } else {
        // Output if no matches were found
        fprintf(outputFp, "No matches found for query: %s\n", result->suburbQuery);
    }
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
