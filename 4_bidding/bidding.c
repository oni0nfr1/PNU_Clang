#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BID_MAX 10001
#define MAX_NAME_LEN 16

typedef struct {
    char name[MAX_NAME_LEN];
    int bid;
} person;

void solve(int N, person *people){
    for (int i = 0 ; i < N ; i++) {
        scanf("%s %d", &people[i].name, &people[i].bid);
    }

    person bidder;
    int bidder_count = 0;
    int bid_max = BID_MAX;
    do{
        strcpy(bidder.name, "NONE");
        bidder.bid = 0;
        bidder_count = 0;

        for (int i = 0 ; i < N ; i++) {
            if (people[i].bid < bid_max) {
                if(bidder.bid < people[i].bid) {
                    bidder = people[i];
                    bidder_count = 1;
                } else if (bidder.bid == people[i].bid) {
                    bidder_count++;
                }
            }
        }
        bid_max = bidder.bid;
    } while (bidder_count != 1 && bidder.bid);
    
    printf("%s", bidder.name);
}

int main() {
    // N의 값이 아주 클 수도 있고 아주 작을 수도 있으므로, 동적 할당을 이용해 포인터를 solve()에 넘겨줌
    int N;
    scanf("%d", &N);
    person *people = malloc(sizeof(person) * N);
    solve(N, people);
    free(people);
}
