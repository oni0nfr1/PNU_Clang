#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *coef;  // 계수 배열
    size_t deg; // 차수
} Polynomial;

// 다항식 구조체 생성자
Polynomial polynomial(size_t deg) {
    int *coef = calloc(deg + 1, sizeof(int));
    return (Polynomial){ coef, deg };
}

// 다항식 구조체 소멸자
void poly_free(Polynomial *poly) {
    free(poly->coef);
    *poly = (Polynomial){0};
}

void poly_grow(Polynomial *poly, size_t new_deg) {
    if (poly->deg < new_deg) {
        poly->coef = realloc(poly->coef, (new_deg + 1) * sizeof(int));
        memset(poly->coef + poly->deg + 1, 0, (new_deg - poly->deg) * sizeof(int));
        poly->deg = new_deg;
    }
}

Polynomial poly_mul(Polynomial poly1, Polynomial poly2) {
    Polynomial result = polynomial(0);
    for (size_t i = 0 ; i <= poly2.deg ; i++) {
        poly_grow(&result, poly1.deg + i);
        for (size_t j = i ; j <= result.deg ; j++) {
            if(j <= poly1.deg + i) result.coef[j] += poly1.coef[j - i] * poly2.coef[i];
        }
    }
    return result;
}

Polynomial poly_input() {
    int len;
    scanf("%d",&len);
    Polynomial poly = polynomial(len - 1);
    for(size_t i = 0 ; i <= poly.deg ; i++) 
        scanf("%d", &poly.coef[i]);
    return poly;
}

int main() {
    Polynomial poly1 = poly_input(),
               poly2 = poly_input(), 
               result = poly_mul(poly1, poly2);
    for (size_t i = 0 ; i <= result.deg ; i++)
        printf("%d ", result.coef[i]);
    poly_free(&poly1);
    poly_free(&poly2);
    poly_free(&result);
}