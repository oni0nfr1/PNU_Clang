#include <stdio.h>
#include <string.h>
#include "mycrack.h"

/**
 * 문자열의 특정 위치에 다른 문자열을 끼워 넣습니다.
 * @param dest 바깥쪽 문자열. 여기에 합쳐진 문자열이 들어감.
 * @param insert 안쪽 문자열.
 * @param pos 안쪽 문자열을 삽입할 위치
 */
void insert_str(char *dest, char *insert, int pos) {
    int len_dest = strlen(dest);
    int len_insert = strlen(insert);

    memmove(dest + pos + len_insert, dest + pos, len_dest - pos + 1);
    memcpy(dest + pos, insert, len_insert);
}

int main() {
    // +1은 null을 위한 자리
    // 문자열의 마지막에는 항상 null이 와야 끝난 것으로 간주됨.
    char *word1, *word2, guess[30+1];
    myready();

    word1 = getword1();
    word2 = getword2();

    int word1_len = strlen(word1);
    int word2_len = strlen(word2);

    for (int i = 0 ; i < word1_len ; i++) {
        strcpy(guess, word1);
        insert_str(guess, word2, i);

        if(crack(guess)) {
            got_it(guess);
            return 0;
        }
    }

    for (int i = 0 ; i < word2_len ; i++) {
        strcpy(guess, word2);
        insert_str(guess, word1, i);

        if(crack(guess)) {
            got_it(guess);
            return 0;
        }
    }

    printf("WTH???"); // 테스트용 코드
    return 0;
}