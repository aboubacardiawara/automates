#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macros.h"

typedef struct ens_state_s
{
    int states[N_STATE];
} set_state;

/**
 * initial an empty set of states.
 */
set_state* create_set_state() {
    int i;
    set_state *p_states;
    p_states = malloc(sizeof(struct ens_state_s));
    for (i = 0; i < N_STATE; i++)
    {
        p_states->states[i] = -1;
    }
    return p_states;
}


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
 * check if a giving set contain at least one final state.
 * @param state{int} a state position.
 * @return 1 if right, 0 else if.
 */
int containFinalState(set_state *set) {
    int i, state;
    for ( i = 0; i < N_STATE; i++)
    {
        state = set->states[i]; 
        if (FINAL_STATES[state] != -1) 
            return 1; 
    }
    return 0;
    
}

void clean_set(set_state* set) {
    int i;
    for (i = 0; i < N_STATE; i++)
    {
        set->states[i] = -1; /*the state represented by -1 doesn't exist*/
    }
}

int add_state_to_set(set_state* set, int state) {
    int i;
    for (i = 0; i < N_STATE; i++)
    {
        if ( set->states[i]==-1 ) {
            set->states[i] = state;
            return 0;
        }
    }
    return -1;
}

void print_set(set_state *set) {
    int i;
    printf("{");
    for (i = 0; i < N_STATE; i++)
    {
        printf("%d, ", set->states[i]);
    }
    
    printf("}\n");
}

/**
 * @param word{string} a word to check with an automate.
 * @return 1 if the automate accept the word, 0 if else.
 */
int check_word(char* word) {
    char character;
    int i, j, state, nextState, k;
    int word_length = len(word);
    set_state s[MAX_CHAR_SIZE];
    set_state* set0;
    set_state *current_set = create_set_state() ;
    set0 = create_set_state();
    add_state_to_set(set0, 0);
    s[0] = *set0;
    
    /* INITIAL STATE, it contains only state 0*/
    
    for (i = 0; i < word_length; i++)
    {
        character = word[i];
        printf("caractère -> %c\n", character);
        /*remplir l'ensemble des etats suivants à partir de l'actuel*/
        for (j = 0; j < N_STATE; j++)
        {
            if (s[i].states[j] != -1 ) {
                state = s[i].states[j];
                if (state != -1) {
                    for (k = 0; k < N_STATE; k++)
                    {
                        nextState = TRANSITIONS[state][lettre2int(character)][k];
                        if (nextState != -1) {
                            add_state_to_set(current_set, nextState);
                        }
                    }
                }
            }
        }
        print_set(current_set);     
        s[i+1] = *current_set; /*ensemble des transitions decoulant de l'etat precedants*/
        clean_set(current_set);
    }
    
    if (containFinalState(&s[word_length]))
        return 1;
    return 0;
}

/**
 * @return 0 if the program runs perfectly.
 * -1 if an error occured.
 */
int main(int argc, char *argv[]) 
{

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
            printf("SUCCES!\n");
        }
        else {
            printf("ECHEC! \n");
        }
    }

    return 0;
}