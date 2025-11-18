#include <stdio.h>

struct Complex {
    double a; 
    double b; 
};

struct Complex add(struct Complex z1, struct Complex z2) {
    struct Complex res = {z1.a + z2.a, z1.b + z2.b};
    return res;
}

struct Complex multiply(struct Complex z1, struct Complex z2) {
    struct Complex res = {z1.a * z2.a - z1.b * z2.b, z1.a * z2.b + z1.b * z2.a};
    return res;
}

struct Complex scalar_mult(struct Complex z, double k) {
    struct Complex res = {z.a * k, z.b * k};
    return res;
}

struct Complex power(struct Complex z, int n) {
    struct Complex res = {1.0, 0.0};
    for (int i = 0; i < n; i++) {
        res = multiply(res, z);
    }
    return res;
}

struct Complex exp_complex(struct Complex z, int terms) {
    struct Complex sum = {1.0, 0.0}; 
    for (int n = 1; n <= terms; n++) {
        struct Complex term = power(z, n);

        double fact = 1.0;
        for (int i = 1; i <= n; i++) fact *= i;

        term = scalar_mult(term, 1.0 / fact);
        sum = add(sum, term);
    }
    return sum;
}

void print_complex(struct Complex z) {
    if (z.b >= 0)
        printf("%.4f + %.4fi\n", z.a, z.b);
    else
        printf("%.4f - %.4fi\n", z.a, -z.b);
}

int main(void) {
    struct Complex z = {1.0, 1.0}; 

    printf("Вычисление exp(z) для z = ");
    print_complex(z);

    struct Complex result = exp_complex(z, 15); 
    printf("exp(z) ≈ ");
    print_complex(result);

    return 0;
}