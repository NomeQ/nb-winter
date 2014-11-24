/*
 * 31-game.c
 * Copyright (c) 2014 Naomi Dickerson and Parker Harris Emerson
 * Given a partially played game of 31, calculate who will win if both parties subsequently play optimally.
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "game_tree.h"


int main(){
    int cards[14];
    int cardIndex = 0;
    char nextChar;

	FILE *fileHandle; //the file containing game 31 data
	fileHandle = fopen("cardData.txt","r");

	// check for file open error
	if (fileHandle == NULL) {
		printf("\nUnable to open game 31 text data\n");
		exit(1);
	}

    while (1) { // Outer loop for file.
        // Clear vars.
        for (int i = 0; i < 14; i++) {
            cards[i] = 0;
        }
        cardIndex = 0;

        while (1) { // Inner loop for each game.
            fscanf(fileHandle, "%c", &nextChar);
            if (nextChar - 48 < 0 || nextChar - 48 > 6) {
                break;
            }
            if (nextChar - 48 == 0) {
                printf("\nEnd of file.\n\n");
                exit(0);
            }
            cards[cardIndex] = (int)(nextChar - 48);
            cardIndex++;
        }

        // Print game.
        for (int i = 0; i < 14; i++) {
            if (cards[i]) {
                printf("%d", cards[i]);
            }
        }
        int winner;
        node gameRoot = { 0 };
        treeCreate(&gameRoot); // Create root node.
        // Copy starting state into root node.
        for (int i = 0; i < 14; i++) {
            gameRoot.state[i] = cards[i];
        }
        gameRoot.owner = 1 + (cardIndex % 2);

        treePopulate(&gameRoot);
        if (gameRoot.isLeaf) {
            winner = cardIndex % 2;
        } else {
            winner = miniMax(&gameRoot);
        }

        if (winner == 1) {
            printf("\tA");
        } else {
            printf("\tB");
        }

        printf("\n");

        for (int i = 0; i < 6; i++) {
            if (gameRoot.child[i]) {
                treeDestroy(gameRoot.child[i]);
            }
        }
    }

    return 0;
}
