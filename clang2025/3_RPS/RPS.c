#include <stdio.h>
#define N_MAX 20

int N;
char game[N_MAX] = "";

void print_winners(char winner, int round) {
    printf("%d\n", round);
    for(int i = round ; i < N ; i++) {
        if(game[i] == winner) printf("%d ", i+1);
    }
}

int main() {
    int r = 0, p = 0, s = 0;

    scanf("%d" ,&N);
    for (int i = 1 ; i <= N ; i++) {
        scanf(" %c" ,&game[i-1]);
        switch (game[i-1]) {
            case 'R': r = i; break;
            case 'P': p = i; break;
            case 'S': s = i; break;
        }
    }

    int kind = (r > 0) + (p > 0) + (s > 0);
    if (kind >= 2) {
        int t = p < s ? p : s;
        int min = r < t ? r : t;
        if      (r == min)  print_winners('S', min);
        else if (p == min)  print_winners('R', min);
        else   /*s == min*/ print_winners('P', min);
    } else {
        printf("0\n0");
    }
}