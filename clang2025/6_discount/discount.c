#include <stdio.h>
#define true 1
#define false 0

typedef enum {
    ALLSTD,
    OVRTEN,
    EVERYM,
    ALLOLD,
    ALLJUR,
    BENEFIT_COUNT
} Benefits;

typedef struct {
    int price;
    int oldmax;
    int oldmin;
    int jurmax;
    int discount;
} context;

void ALLSTD_discount(context *ctx){ (*ctx).discount += 15                                    ; }
void OVRTEN_discount(context *ctx){ (*ctx).discount += 10                                    ; }
void EVERYM_discount(context *ctx){ (*ctx).price    -= (*ctx).oldmax - (*ctx).oldmax * 4 / 5 ; }
void ALLOLD_discount(context *ctx){ (*ctx).price    -= (*ctx).oldmin                         ; }
void ALLJUR_discount(context *ctx){ (*ctx).price    -= (*ctx).jurmax - (*ctx).jurmax * 7 / 10; }

typedef void (*benefit)(context*);
benefit benefits[BENEFIT_COUNT] = {
    ALLSTD_discount,
    OVRTEN_discount,
    EVERYM_discount,
    ALLOLD_discount,
    ALLJUR_discount
};

context getContext(int N, int flag[BENEFIT_COUNT]) {
    context ctx = {0};

    flag[OVRTEN] = (N >= 10);
    int stdcount = 0;
    int oldcount = 0;
    int jurcount = 0;
    flag[ALLSTD] = true; // 먼저 true로 해 두고, STD가 아닌 것이 나오면 false로 설정
    for(int i = 0 ; i < N ; i++) {
        char type[3+1]; //3글자 + null 1바이트
        int price;
        scanf("%s %d", type, &price);
        // switch-case문을 통해 최적화
        // 문자열은 라벨에 못 쓰므로 첫 글자만 따서 손님 구분
        switch (type[0]){
        case 'S':
            stdcount++;
            ctx.price += price;
            break;
        case 'O':
            oldcount++;
            ctx.price += price;
            if (oldcount == 1 || price > ctx.oldmax) ctx.oldmax = price;
            if (oldcount == 1 || price < ctx.oldmin) ctx.oldmin = price;
            flag[ALLSTD] = false;
            break;
        case 'J':
            jurcount++;
            ctx.price += price;
            if (jurcount == 1 || price > ctx.jurmax) ctx.jurmax = price;
            flag[ALLSTD] = false;
            break;
        case 'A':
            ctx.price += price;
            flag[ALLSTD] = false;
            break;
        }
    }

    flag[EVERYM] = stdcount && oldcount && jurcount;
    flag[ALLSTD] = flag[ALLSTD] && (N >= 5);
    flag[ALLOLD] = oldcount >= 6;
    flag[ALLJUR] = jurcount >= 5;
    return ctx;
}

int main() {
    int N; scanf("%d", &N);
    
    int flag[BENEFIT_COUNT] = {0};
    context ctx = getContext(N, flag);

    //3, 4, 5번 혜택부터 적용되어야 하므로 역순으로 순회
    for (int benefit_type = BENEFIT_COUNT-1 ; benefit_type >= 0 ; benefit_type--) {
        if(flag[benefit_type]) benefits[benefit_type](&ctx); //함수 포인터 이용
    }

    printf("%d", ctx.price * (100 - ctx.discount) / 100);
}