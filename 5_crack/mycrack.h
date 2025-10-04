#include <stdio.h>
#include <string.h>

int crack_count = 0;

char word1[15] = "clang";
char word2[15] = "pusan";
char password[30] = "pusclangan";

void myready() {
    printf("[TEST] mycrack.h ready.\n");
}

char *getword1() {
    printf("[TEST] word1 is \"%s\"\n", word1);
    return word1;
}

char *getword2() {
    printf("[TEST] word2 is \"%s\"\n", word2);
    return word2;
}

int crack(char *myguess) {

    printf("[TEST] you guessed \"%s\".\n", myguess);

    crack_count++;
    int is_correct = strcmp(password, myguess) == 0;

    if(is_correct) {
        printf("[TEST] your guess is correct!\n");
    } else {
        printf("[TEST] your guess is incorrect.\n");
    }

    return is_correct;
}

void got_it(char *myguess) {
    printf("[TEST] got_it called.\n");
    printf("[TEST] your guess is \"%s\".\n", myguess);

    int is_correct = strcmp(password, myguess) == 0;

    printf("\n\n\n");
    if(is_correct) {
        printf("Congrats! you solved the problem!\n");
    } else {
        printf("Nice try. But Failed to solve the problem.\n");
    }
    printf("total crack count: %d\n\n", crack_count);
}