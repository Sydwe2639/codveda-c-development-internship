/*
 * Level 1 (Basic) - Task 2: Number Guessing Game
 *
 * Description: The program generates a random number between 1 and 100,
 * and the user tries to guess it within a limited number of attempts,
 * receiving "too high" / "too low" feedback after each guess.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ATTEMPTS 7
#define LOWER_BOUND 1
#define UPPER_BOUND 100

int main(void) {

    int target, guess, attempts = 0;
    int guessed = 0;

    srand((unsigned int)time(NULL)); //seed
    target = (rand() % (UPPER_BOUND - LOWER_BOUND + 1)) + LOWER_BOUND; //random number between 1 and 100

    printf("===== Number Guessing Game =====\n");
    printf("I have picked a number between %d and %d.\n", LOWER_BOUND, UPPER_BOUND);
    printf("You have %d attempts to guess it.\n\n", MAX_ATTEMPTS);

    while (attempts < MAX_ATTEMPTS && !guessed){  // Keep looping till found number or out of attempts
        printf("Attempt %d/%d - Enter your guess: ", attempts + 1, MAX_ATTEMPTS);

        if (scanf("%d", &guess) != 1) {
            printf("Invalid input. Please enter an integer.\n");
            /* clear bad input from stdin */
            while (getchar() != '\n');
            continue;
        }

        attempts++;

        if (guess == target) { //If the guess is correct
            guessed = 1;
            printf("Congratulations! You guessed the number %d correctly in %d attempt(s)!\n",
                   target, attempts);
        } else if (guess < target) {
            printf("Too low! Try again.\n\n");
        } else {
            printf("Too high! Try again.\n\n");
        }
    }

    if (!guessed) { //Did not get the number and out of Attempts
        printf("\nOut of attempts! The number was %d. Better luck next time!\n", target);
    }

    return 0;
}
