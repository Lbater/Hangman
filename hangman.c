#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
Author: Logan Bateman
Date-Started: 23/4/24
Date-finished: 24/4/24
Date-Prettyfied: 28/4/24
*/

/*
This Just helps me to realize the scope of the project

1. Initialization:
    -Define an array of words to be used in the game. - Done
    -Randomly select a word from the array. - Done
2. Main Game Loop:
    -Display the initial state of the word (e.g., underscores for each letter). - Done
    -Prompt the user to guess a letter. - Done
    -Check if the guessed letter is in the word:
        -If it is, reveal the letter(s) in the word. - Done
        -If it's not, decrement the number of remaining guesses and update the hangman figure if needed. - Done
    -Continue the loop until the word is guessed correctly or the number of guesses runs out.
3. Functions:
    -Implement functions for tasks like selecting a random word(Done), checking if a letter is in the word (Done), updating the hangman figure, etc. This will make your code more modular and easier to understand. //Ori would be proud it wants modularity
4. Win/Lose Conditions:
    -Determine when the player has won or lost the game (e.g., all letters guessed correctly or run out of guesses). -Done
    -Display appropriate messages to the player. - Done
*/

/**
 * This randomly picks a word from a list of 10
 * limited to 10 becasue i'm lazy
 * This was rewritten by blaockbox because i couldn't figure it out
 * 
 * @return char* The word that was randomly picked
*/
char* wordPicker(){
    srand(time(NULL));
    int r = rand() % 10;

    char *wordArray[] = {
        "hallo",
        "mango",
        "dinosaur",
        "abyss",
        "subway",
        "jazz",
        "rythm",
        "askew",
        "galaxy",
        "starwars"
    };

    char *chosenWord = malloc(strlen(wordArray[r]) + 1);

    if(chosenWord == NULL){
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    strcpy(chosenWord, wordArray[r]);

    return chosenWord;
}

/**
 * This takes the word and converts is into the underscores
 * 
 * @param word The word to be converted
 * @return The word with underscores
*/
char* scrambler(char *word){
    // Print the original word
    //printf("Original word: %s\n", word); //re add this for debugging purposes

    // Allocate memory for newWord
    char *newWord = malloc(strlen(word) + 1); // +1 for null terminator

    if (newWord == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Copy the original word to newWord
    strcpy(newWord, word);

    // Replace characters with underscores
    for(int i = 0; i < strlen(newWord); i++){
        if(newWord[i] != ' '){
            newWord[i] = '_';
        }
    }

    // Print the modified word
    printf("Modified word: %s\n", newWord);

   return newWord;
}  

/**
 * This checks if the guessed letter is in the word chosen
 * 
 * @param word the word chosen
 * @param guess the letter guessed
 * @param newWord the modified word
*/
void guesser(char *word, char *guess, char *newWord){
    int numGuess = 9;
    while(numGuess > 0){
        int found = 0;
        for(int i = 0; i < strlen(word); i++){
            if(word[i] == *guess){
                word[i] = *guess;
                newWord[i] = *guess;
                printf("That\'s correct. Keep going!\n%s\n", newWord);
                found = 1; //basically working the way booleans work
            }
        }
        if(!found){
            printf("That\'s to bad. Try again.\n");
        }
        numGuess--;
        if(strcmp(word, newWord) == 0){
            printf("Congrats are in order my guy\n");
            char playAgain;
            printf("Do you want to play again?(y/n) ");
            scanf(" %c", &playAgain);
            switch(playAgain){
                case 'y':
                case 'Y':
                    gameLoop();
                    break;
                case 'n':
                case 'N':
                    printf("Thanks for playing!\n");
                    exit(EXIT_SUCCESS);
                    break;
            }
            break;
        }
        if(numGuess == 0){
            printf("You loose my guy.\n");
            char playAgain;
            printf("Do you want to play again?(y/n) ");
            scanf(" %c", &playAgain);
            switch(playAgain){
                case 'y':
                case 'Y':
                    gameLoop();
                    break;
                case 'n':
                case 'N':
                    printf("Thanks for playing!\n");
                    exit(EXIT_SUCCESS);
                    break;
            }
            break;
        }
        printf("Guess a letter you have \'%d\' guesses left: ", numGuess);
        scanf(" %c", guess);
    }   
}

/**
 * This is where the game loop logic happens
 */
void gameLoop(){
    char *chosenWord = wordPicker();    
    char *scrambled = scrambler(chosenWord);
    
    char guess;
    printf("Guess a letter 10 tries remaining: ");
    scanf(" %c", &guess);

    guesser(chosenWord, &guess, scrambled);
    
    // Free dynamically allocated memory
    free(scrambled);
    free(chosenWord);
}

/**
 * This is the main part of the project
 */
int main(){
    char start;
    printf("Do you want to pplay Hangman?(y/n) ");
    scanf(" %c", &start);

    switch(start){
        case 'y':
        case 'Y':
            char rules;
            printf("Do you need the rules?(y/n) ");
            scanf(" %c", &rules);

            switch(rules){
                case 'y':
                case 'Y':
                    printf("You have 10 tries to guess a randomly chosen word from a list of 10.\n");
                    printf("You can guess an entire word however it will take guesses for every letter you guess. Use wisely");
                    printf("Your ready now. Good luck\n");
                case 'n':
                case 'N':
                    //Either the user said no to the rules or they said yes and we already printed the rules
                    //Start the Game
                    gameLoop();              
                    break;
                default:
                    printf("Invalid input.\n");
            }
        case 'n':
        case 'N':
            printf("Ok, bye!\n");
            break;
        default:
            printf("Invalid input.\n");
    }
    return 0;
}