#include <stdio.h>
#include <math.h>
// 원주율 타우는 원주율 파이의 2배입니다. 호도법에서 육십분법으로 변환하면 360도가 됩니다.
#define TAU (2.0 * acos(-1.0))

/** 
 * 가두리의 정보를 담은 구조체입니다.
 * 중심의 x좌표, y좌표, 둘레 r을 short 자료형으로 저장합니다.
 */
struct Gaduri {
    short x;
    short y;
    short r;
};

/** 두 부채꼴의 중심 사이의 거리를 구합니다. */
double getDist(struct Gaduri a, struct Gaduri b) {
    int x = a.x - b.x;
    int y = a.y - b.y;
    return hypot(a.x - b.x, a.y - b.y);
}

/** 둘레 중 가두리를 잇는 부분 */
double getNewLineLength(struct Gaduri a, struct Gaduri b) {
    double bottom = a.r - b.r;
    double hyp = getDist(a, b);
    return sqrt((hyp - bottom) * (hyp + bottom));
}

/** 넓이에서 부채꼴 부분의 중심각을 구합니다. */
double getAngle(struct Gaduri a, struct Gaduri b) {
    double h = getNewLineLength(a, b);
    double bottom = a.r - b.r;
    return atan2(h, bottom) * 2.0;
}

/** 최종 전체 넓이를 구합니다. */
double getTotalArea(struct Gaduri a, struct Gaduri b) {
    double theta = getAngle(a, b);
    double h = getNewLineLength(a, b);

    double trapezoid = (a.r + b.r) * h;

    double sector1 = 0.5 * a.r * a.r * (TAU - theta);
    double sector2 = 0.5 * b.r * b.r * theta;

    return trapezoid + sector1 + sector2;
}

/** 최종 전체 둘레를 구합니다. */
double getTotalCircumference(struct Gaduri a, struct Gaduri b) {
    double theta = getAngle(a, b);
    double h = getNewLineLength(a, b);

    double arc1 = (TAU - theta) * a.r;
    double arc2 = theta * b.r;

    return arc1 + arc2 + 2 * h;
}

int main(void) {
    struct Gaduri g1, g2;
    scanf("%hd %hd %hd", &(g1.x), &(g1.y), &(g1.r));
    scanf("%hd %hd %hd", &(g2.x), &(g2.y), &(g2.r));

    double area = getTotalArea(g1, g2);
    double circum = getTotalCircumference(g1, g2);

    printf("%d %d", (int)circum, (int)area);
    return 0;
}
