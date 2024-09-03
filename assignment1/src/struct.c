#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "../include/struct.h"

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

void outputSearchResults(FILE *outputFp, QueryResult *result) {
    // Check if there are matching records
    if (result->matchesFound > 0) {
        SuburbRecord *current = result->matches;
        
        // Loop through the linked list of matching records
        fprintf(outputFp, "%s -->\n", result->suburbQuery);
        while (current) {
            fprintf(outputFp, "COMP20003 Code: %d, Official Code Suburb: %d, Official Name Suburb: %s, Year: %d, Official Code State: %d, Official Name State: %s, Official Code Local Government Area: %s, Official Name Local Government Area: %s, Latitude: %.7lf, Longitude: %.7lf\n",
                current->comp20003_code, current->official_code_suburb, current->official_name_suburb,
                current->year, current->official_code_state, current->official_name_state,
                current->official_code_lga, current->official_name_lga, current->latitude, current->longitude);
            // Move to the next record in the list
            current = current->next;
        }
    }
}