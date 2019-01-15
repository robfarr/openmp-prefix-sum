/**
 * A parallel implementation of a left-associative prefix sum using OpenMP
 */
#include <stdio.h>
#include <string.h>
#include <omp.h>

int* prefix_scan(const int* input, size_t len);
void print_array(int* data, size_t len);

/**
 * Entry point
 *
 * @return Exit status
 */
int main() {

    int data[] = {1, 2, 3, 4, 5};
    size_t len = 5;
    print_array(data, len);

    int* output = prefix_scan(data, len);
    print_array(output, len);

    return 0;
}

/**
 * Parallel left-associative prefix sum operation
 *
 * @param input The array of integers to perform a prefix scan half-reduction on
 * @param len   The number of items in the input array
 * @return      A pointer to a new array containing the reduced values
 */
int* prefix_scan(const int* input, size_t len) {

    int* output = calloc(len, sizeof(int));

    for (int apart=0; apart<len; apart++) {

        #pragma omp parallel for
        for (int i=apart; i<len; i++) {
            output[i] += input[i-apart];
        }

    }

    return output;

}

/**
 * Outputs an array of integers to STDOUT
 *
 * @param data  The array of integers to output
 * @param len   The number of items in data to output
 */
void print_array(int* data, size_t len) {
    for (int i=0; i<len; i++) {
        char delimit = (char) (i == len-1 ? '\n' : ',');
        printf("%d%c", data[i], delimit);
    }
}