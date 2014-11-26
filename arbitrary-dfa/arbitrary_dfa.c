/*
 * arbitrary_dfa.c
 *
 * Naomi Dickerson 2014
 */
/*A DFA program that reads the DFA = {Q,E,q(0),{q(a)},D} from
 * a given file. The file must be of the format number of states,
 * states, number of elements in the alphabet, the characters of the
 * alphabet, the start state, the number of accept states, the accepting
 * states, and the table of transitions. */

#include <stdio.h>
#include <stdlib.h>

int inAlphabet(char* alphabet, int alphabet_size, char x) {
    for (int i = 0; i < alphabet_size; i++) {
        if (alphabet[i] == x) {
            return 1;
        }
    }

    return 0;
}

int checkContinue() {
    printf("\nWould you like to test another string?(y/n) ");
    char temp;
    char new;
    scanf("%c", &temp); //FLUSH
    scanf("%c", &new);

    if (new == 'y') {
        return 1;
    }
    else {
        return 0;
    }
}

int checkAccept(int* accept_states, int num_accepts, int current_state) {
    for (int i = 0; i < num_accepts; i++) {
        if (accept_states[i] == current_state) {
            return 1;
        }
    }

    return 0;
}

int main (int argc, char* argv[]) {
    int start_state, alphabet_size, num_states, num_accepts, current_state;
    char end_char;
    int** delta_table = NULL;
    int* states = NULL;
    char* alphabet = NULL;
    int* accept_states = NULL;

    FILE* fileHandle = fopen("dfa_data.txt", "r");

    {
        // Read in the number of states, malloc space for
        // them in the array "states", and put in each state.
        fscanf(fileHandle, "%d", &num_states);

        states = (int*) (malloc(sizeof(int) * num_states));
        for (int i = 0; i < num_states; i++) {
            fscanf(fileHandle, "%d", &states[i]);
        }
    }
    {
        // Read in the size of the alphabet then read
        // in the alphabet from file.
        fscanf(fileHandle, "%d", &alphabet_size);

        alphabet = (char*) (malloc(sizeof(char) * alphabet_size));
        for (int i = 0; i < alphabet_size; i++) {
            fscanf(fileHandle, " %c", &alphabet[i]);
        }
    }
    {
        // Read in the stop char
        fscanf(fileHandle, " %c", &end_char);
    }
    {
        // Read in the start state
        fscanf(fileHandle, "%d", &start_state);
    }
    {
        // Read in the number of accept states, then put them in array
        fscanf(fileHandle, "%d", &num_accepts);

        accept_states = (int*) (malloc(sizeof(int) * num_accepts));
        for (int i = 0; i < num_accepts; i++) {
            fscanf(fileHandle, "%d", &accept_states[i]);
        }
    }
    {
        // Read in the transition table
        delta_table = (int**) (malloc(sizeof(int*) * num_states));

        for (int i = 0; i < num_states; i++) {
            delta_table[i] = (int*) (malloc(sizeof(int) * alphabet_size));
        }

        for (int i = 0; i < num_states; i++) {
            for (int j = 0; j < alphabet_size; j++) {
                fscanf(fileHandle, "%d", &delta_table[i][j]);
            }
        }
    }

    fclose(fileHandle);

    // Create a loop to allow the user to test multiple strings without
    // re-opening and re-reading the dfa file.
    int intContinue = 1;
    char x = NULL;
    while (intContinue) {
        current_state = start_state;
        printf("\nEntry: ");

        while (1) {
            scanf("%c", &x);

            if (x == end_char) {
                break;
            }

            else if (inAlphabet(alphabet, alphabet_size, x)) {
                // Make sure 'x' is in the alphabet first
                current_state = delta_table[current_state][(int) (x - 'a')];
            }
            // Currently does nothing with input that's not in alphabet.
            // Simply ignores it.
        }

        if (checkAccept(accept_states, num_accepts, current_state)) {
            printf("\naccept\n");
        } else {
            printf("\nreject\n");
        }

        intContinue = checkContinue();
    }

    return 0;
}

