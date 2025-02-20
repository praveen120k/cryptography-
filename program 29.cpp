#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#define STATE_SIZE 25      // 5x5 state matrix (each element is a 64-bit lane)
#define BLOCK_SIZE 1024    // 1024-bit block size
#define LANE_SIZE 64       // Each lane is 64-bit
#define CAPACITY_LANES 9   // Capacity size: (1600 - 1024) / 64 = 9 lanes

uint64_t state[STATE_SIZE] = {0};  // SHA-3 state (all zero at the start)

// Function to simulate absorbing a message block (P0)
void absorb_message_block(uint64_t message[STATE_SIZE - CAPACITY_LANES]) {
    for (int i = 0; i < STATE_SIZE - CAPACITY_LANES; i++) {
        state[i] ^= message[i]; // XOR message into state
    }
}

// Function to check if all capacity lanes have at least one nonzero bit
int all_capacity_lanes_nonzero() {
    for (int i = STATE_SIZE - CAPACITY_LANES; i < STATE_SIZE; i++) {
        if (state[i] == 0) {
            return 0; // At least one lane is still zero
        }
    }
    return 1; // All capacity lanes have nonzero bits
}

int main() {
    srand(time(NULL));

    int blocks_needed = 0;
    uint64_t message[STATE_SIZE - CAPACITY_LANES];

    printf("Starting SHA-3 simulation with block size of %d bits...\n", BLOCK_SIZE);

    // Keep absorbing message blocks until all capacity lanes have nonzero bits
    while (!all_capacity_lanes_nonzero()) {
        // Generate a random message block ensuring at least one nonzero bit per lane
        for (int i = 0; i < STATE_SIZE - CAPACITY_LANES; i++) {
            message[i] = (uint64_t)rand() << 32 | rand(); // Random 64-bit value
        }

        // Absorb the message block
        absorb_message_block(message);
        blocks_needed++;
    }

    printf("All capacity lanes contain at least one nonzero bit after %d message blocks.\n", blocks_needed);
    return 0;
}

