#include <stdio.h>

void testcase() {
    unsigned char longest = 0, count = 0;
    unsigned long long number;
    scanf("%llu" ,&number);
    while(number) {
        unsigned short curr_run = 0;
        while(number & 1) {
            curr_run++;
            number >>= 1;
        }
        if(longest < curr_run && curr_run > 1){
            longest = curr_run;
            count = 1;
        } else if (longest == curr_run && curr_run > 1) {
            count++;
        }
        number >>= 1;
    }
    printf("%hhu %hhu\n" ,longest ,count);
}

int main() {
    for(int i = 0 ; i < 5 ; i++) testcase();
}