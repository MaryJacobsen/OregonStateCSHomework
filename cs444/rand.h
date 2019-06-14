#ifndef RAND_H
#define RAND_H

#include <stdint.h>
#include <stddef.h>

// Get a random production period in the integer range [3,7).
unsigned int get_random_production_period();

// Get a random waiting period in the integer range [2,9).
unsigned int get_random_waiting_period();

unsigned int get_random_number();

// Initialize the rng
void random_number_init();

uint32_t cpu_supports_rdrand();
uint32_t native_get_random_number();

#endif
