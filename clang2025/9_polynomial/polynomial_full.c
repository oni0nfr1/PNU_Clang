#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *coef;  // 계수 배열
    size_t deg; // 차수
} Polynomial;

// 다항식 구조체 생성자
Polynomial polynomial(size_t deg) {
    if (deg == SIZE_MAX) return (Polynomial){ .coef = NULL, .deg = 0 };
    int *coef = calloc(deg + 1, sizeof *coef);
    if (!coef)   return (Polynomial){ .coef = NULL, .deg = 0 };
    return (Polynomial){ .coef = coef, .deg = deg };
}

// 다항식 구조체 소멸자
void poly_free(Polynomial *poly) {
    if (!poly) return;
    if (poly->coef) free(poly->coef);
    *poly = (Polynomial){0};
}

void poly_grow(Polynomial *poly, size_t new_deg) {
    if (!poly) return;
    if (poly->deg < new_deg) {
        poly->coef = realloc(poly->coef, (new_deg + 1) * sizeof *(poly->coef));
        memset(poly->coef + poly->deg + 1, 0, (new_deg - poly->deg) * sizeof *(poly->coef));
        poly->deg = new_deg;
    }
}

Polynomial poly_scale(Polynomial poly, int scalar) {
    Polynomial result = polynomial(poly.deg);
    for (size_t i = 0; i <= result.deg ; i++) {
        result.coef[i] = poly.coef[i] * scalar;
    }
    return result;
}

Polynomial poly_shift(Polynomial poly, size_t shift) {
    Polynomial result = polynomial(poly.deg + shift);
    for (size_t i = shift ; i <= result.deg ; i++) {
        result.coef[i] = poly.coef[i-shift];
    }
    return result;
}

Polynomial poly_shift_scale(Polynomial poly, size_t shift, int scalar) {
    Polynomial result = polynomial(poly.deg + shift);
    for (size_t i = shift ; i <= result.deg ; i++) {
        result.coef[i] = poly.coef[i-shift] * scalar;
    }
    return result;
}

Polynomial poly_add(Polynomial poly1, Polynomial poly2) {
    size_t result_deg = (poly1.deg > poly2.deg) ? poly1.deg : poly2.deg;
    Polynomial result = polynomial(result_deg);
    for (size_t i = 0 ; i <= result_deg ; i++) {
        if (i <= poly1.deg) result.coef[i] += poly1.coef[i];
        if (i <= poly2.deg) result.coef[i] += poly2.coef[i];
    }
    return result;
}

Polynomial poly_mul(Polynomial poly1, Polynomial poly2) {
    Polynomial result = polynomial(0);
    for (size_t i = 0 ; i <= poly2.deg ; i++) {
        Polynomial _result = result;
        Polynomial shifted = poly_shift(poly1, i);
        Polynomial scaled  = poly_scale(shifted, poly2.coef[i]);
        poly_free(&shifted);
        result = poly_add(_result, scaled);
        poly_free(&scaled);
        poly_free(&_result);
    }
    return result;
}

static void poly_simple_mul(Polynomial *out, Polynomial src, size_t order, int coef) {
    size_t new_deg = (out->deg > src.deg + order) ? out->deg : (src.deg + order);
    poly_grow(out, new_deg);
    for (size_t i = order ; i <= out->deg ; i++)
        if(i <= src.deg + order) out->coef[i] += src.coef[i - order] * coef;
}

Polynomial poly_mul2(Polynomial poly1, Polynomial poly2) {
    Polynomial result = polynomial(0);
    for (size_t i = 0 ; i <= poly2.deg ; i++)
        poly_simple_mul(&result, poly1, i, poly2.coef[i]);
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

}

