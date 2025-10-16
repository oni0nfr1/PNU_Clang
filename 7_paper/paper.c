// Paper, Box를 넘어서 임의의 N차원까지 대응 가능한 코드
#include <stdio.h>
#include <stdlib.h>

// 2차원 문제 (Paper)
#define DIMENSION 2
#define TESTCASES 4
#undef NULL
// NULL을 다른 값으로 쓰므로 #define NULL ((void *)0)을 취소

#define POINT 0
#define LINE  1
#define FACE  2
#define VOL   3
#define NULL -DIMENSION
// 그냥 음수면 NULL로 취급

#define INDEXOF(dim, i) (((DIMENSION) * (i)) + (dim))

void get_figure(int *figure) {
    for (int i = 0 ; i < DIMENSION * 2 ; i++) {
        scanf("%d", figure + i);
    }
}

int evaluate_1d(int lo1, int hi1, int lo2, int hi2) {
    if      (hi1 < lo2)  return NULL;
    else if (hi1 == lo2) return POINT;

    if      (hi2 < lo1)  return NULL;
    else if (hi2 == lo1) return POINT;

    return LINE;
}

int evaluate(int *figure1, int *figure2) {
    int overlap = 0;
    for (int i = 0 ; i < DIMENSION ; i++) {
        int overlap_1d = evaluate_1d(
            figure1[INDEXOF(i, 0)],
            figure1[INDEXOF(i, 1)], 
            figure2[INDEXOF(i, 0)], 
            figure2[INDEXOF(i, 1)]
        );
        overlap += overlap_1d;
    }
    return overlap;
}

void testcase() {
    int figure1[DIMENSION * 2];
    int figure2[DIMENSION * 2];
    get_figure(figure1);
    get_figure(figure2);

    int result = evaluate(figure1, figure2);
    switch(result) {
        case POINT : printf("POINT\n"); break;
        case LINE  : printf("LINE\n") ; break;
        case FACE  : printf("FACE\n") ; break;
        case VOL   : printf("VOL\n")  ; break;
        default    :
        result < 0 ? printf("NULL\n") 
                   : printf("DIM-%d\n", result);
    }
}

int main() {
    int T = TESTCASES;
    while (T--) testcase();
}