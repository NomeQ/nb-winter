/*
 * game_tree.h
 *
 * Provides game_tree structure for 31-game.c
 * Naomi Dickerson and Parker Harris Emerson 2014
 *
 */

#ifndef GAME_TREE_H_
#define GAME_TREE_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct game_node {
    // Creates node containing the game state, the node's
    // 'owner', whether or not it is a leaf (final state) and
    // 6 child nodes.
    int owner;
    int state[14];
    int isLeaf;
    struct game_node* child[6];
} node;

int legalState(int num, int* cur_state) {
    // takes a number "num" (1-6) and sees if it is a valid
    // play given a current game state "cur_state". If yes,
    // return 1. Else return 0.
    int total = 0;
    int total_num = 0;
    int i = 0;
    while (cur_state[i] != 0) {
        total += cur_state[i];
        if (cur_state[i] == num) {
            total_num += 1;
        }
        i++;
    }
    // The card is illegal if it brings the total above 31 or
    // there are already 4 of the card in play.
    if ((total + num) > 31 || total_num >= 4) {
        return 0;
    }
    return 1;
}

void addCard(int num, node* nodeNew) {
    // Finds the first '0' entry in the state array passed in,
    // and appends the given int (card number) at that position.
    int i = 0;
    while (nodeNew->state[i] != 0) {
        i++;
    }
    nodeNew->state[i] = num;
    // A's move
    if ((i % 2) == 1) {
        nodeNew->owner = 1;
    // B's move
    } else {
        nodeNew->owner = 2;
    }
}

void treeCreate(node* nodeRoot) {
    for (int i = 0; i < 14; i++) {
        nodeRoot->state[i] = 0;
    }

    for (int i = 0; i < 6; i++) {
        nodeRoot->child[i] = NULL;
    }
}

node* nodeCreate(int card, node* nodeRoot) {
    node* nodeNew = (node*) (malloc(sizeof(node)));
    for (int i = 0; i < 14; i++) {
        nodeNew->state[i] = nodeRoot->state[i];
    }
    // Appends the new card to the existing game state
    addCard(card, nodeNew);
    for (int i = 0; i < 6; i++) {
        nodeNew->child[i] = NULL;
    }
    return nodeNew;
}

void treePopulate(node* nodeRoot) {
    // Generates all legal games from a given root
    int hasChild = 0;
    for (int i = 0; i < 6; i++) {
        // Check if adding that child creates a legal game state
        if (legalState((i + 1), nodeRoot->state)) {
            // If it is a legal game state, create a variable
            // with the new state to pass to the child
            nodeRoot->child[i] = nodeCreate(i + 1, nodeRoot);
            treePopulate(nodeRoot->child[i]);
            hasChild++;
        }
    }
    if (!hasChild) {
        nodeRoot->isLeaf = 1;
    }
}

int miniMax(node* nodeRoot) {
    // Test if it is a leaf, i.e. the base case of the recursion
    if (nodeRoot->isLeaf) {
        if (nodeRoot->owner == 1) {
            return 1;
        } else {
            return -1;
        }
    } else {
        // Otherwise, if not leaf:
        //(stop searching if the greatest possible max/min found sooner)
        if (nodeRoot->owner == 1) {
            for (int i = 0; i < 6; i++) {
                if (nodeRoot->child[i] && miniMax(nodeRoot->child[i]) == 1) {
                    return 1;
                }
            }
            // This should return -1 only if all of the children are -1
            return -1;
        } else {
            for (int i = 0; i < 6; i++) {
                if (nodeRoot->child[i] && miniMax(nodeRoot->child[i]) == -1) {
                    return -1;
                }
            }
            // opposite of above, returns the min,
            // so only returns 1 if all children are 1
            return 1;
        }
    }
}

void treeDestroy(node* nodeRoot) {

    if (nodeRoot == NULL) {
        return;
    }

    for (int i = 0; i < 6; i++) {
        treeDestroy(nodeRoot->child[i]);
    }
    free(nodeRoot);
}

#endif /* GAME_TREE_H_ */
