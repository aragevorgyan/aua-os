#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define NUM_PLAYERS 8
#define NUM_ROUNDS 5

int main() {
    int scores[NUM_PLAYERS] = {0};  // Store total scores for each player
    srand(time(NULL)); // Seed random number generator

    omp_set_num_threads(NUM_PLAYERS);

    for (int round = 1; round <= NUM_ROUNDS; round++) {
        int dice[NUM_PLAYERS]; // Store dice roll for each player
        int max_roll = 0, winner = -1;

        #pragma omp parallel
        {
            int id = omp_get_thread_num();
            dice[id] = (rand() % 6) + 1; // Roll a 6-sided dice

            #pragma omp barrier // Wait for all players to roll before proceeding

            #pragma omp single
            {
                // Determine the winner of the round
                for (int i = 0; i < NUM_PLAYERS; i++) {
                    if (dice[i] > max_roll) {
                        max_roll = dice[i];
                        winner = i;
                    }
                }
                scores[winner]++; // Update the winner's score
                printf("Round %d: Player %d wins with a roll of %d\n", round, winner, max_roll);
            }

            #pragma omp barrier // Wait for the round to be processed before starting the next
        }
    }

    // Print final scores
    printf("\nFinal Scores:\n");
    for (int i = 0; i < NUM_PLAYERS; i++) {
        printf("Player %d: %d wins\n", i, scores[i]);
    }

    return 0;
}
