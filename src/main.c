#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macros.h"

int TRANSITIONS[N_STATE][ALPHABET_SIZE][N_STATE] = 
    {
        {{1,2,-1,-1},{-1,-1,-1,-1},{-1,-1,-1,-1}},
        {{-1,-1,-1,-1},{0,1,3,-1},{-1,-1,-1,-1}},
        {{-1,-1,-1,-1},{-1,-1,-1,-1},{1,3,-1,-1}},
        {{-1,-1,-1,-1},{-1,-1,-1,-1},{2,-1,-1,-1}}
    };

/*the final states are q1 and q3, q2 q0 aren't*/
int FINAL_STATES[N_STATE] = {0, 1, 0, 1};

/**
 * return a string size.
 * @param srt {char} a string to determin the length.
 * @return the string length.
*/
int len(char* str) {
    char c;
    int length = 0;
    while ( (c = str[length]) != '\0' ) {
        length++;
    }

    return length;
}

/**
 * associate each symbol (alphabetic) to an integer.
 * @param c{char} a char to give the associated integer.
 */
int lettre2int (char c){ 
    int R;
    switch (c) {
        case 'a' : R = 0;
            break;
        case 'b' : R = 1;
            break;
        case 'c' : R = 2;
            break;
        default : R = -1;
    }
    return R;
}

/*!
 * check if a giving state is a final state or not.
 * @param statePosition{int} a state position.
 *
 * Exemple: 0 for q0 or state 0, x for stateX.
 * @return 1 if right, 0 else if.
 */
int isFinalState(int statePosition) {
    if (statePosition -1)
        return 0;
    return FINAL_STATES[statePosition];
}

/**
 * @param word{string} a word to check with an automate.
 * @return 1 if the automate accept the word, 0 if else.
 */
int check_word(char* word) {
    char character;
    int i=0;
    int word_length = len(word);
    int s[N_STATE];
    s[0] = 0;

    for (i = 0; i < word_length; i++)
    {
        character = word[i];
        s[i+1] = TRANSITIONS[s[i]][lettre2int(character)][s[i]];
    }
    
    if (isFinalState(s[word_length]))
        return 1;
    return 0;
}

/**
 * 
 * @return 0 if the program runs perfectly.
 * -1 if an error occured.
 */
int main(int argc, char *argv[]) {
    int isAcceptedWord;

    /*char word[MAX_CHAR_SIZE];*/
    if (argc == 1) {
        printf("Give the word to analyse as argument\n");
        printf("USAGE: ./main <word> \n + replace <word> by the string to analyse\n");
        exit(-1);
    }
    else if(argc > 2) {
        printf("!!(Accept only one argument)\n");
        printf("USAGE: ./main <word> \n + replace <word> by the string to analyse\n");
        exit(-2);
    }
    else {
        isAcceptedWord = check_word(argv[1]);
        if (isAcceptedWord) {
            printf("SUCCES!");
        }
        else {
            printf("ECHEC! \n");
        }
    }

    return 0;
}