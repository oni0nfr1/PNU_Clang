#include <stdio.h>

int main() {
    int N, new, max = 0;
    scanf("%d" ,&N);
    while(N--) {
        scanf("%d" ,&new);
        max = max > new ? max : new;
    }
    max ? printf("%d" ,max) : printf("None");
}