#include <stdio.h>
#include <math.h>
#include <string.h>

struct Vector3D {
    char name[20];
    double x, y, z;
};

double dot_product(struct Vector3D a, struct Vector3D b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

struct Vector3D cross_product(struct Vector3D a, struct Vector3D b, const char* name) {
    struct Vector3D result;
    strncpy(result.name, name, sizeof(result.name));
    result.x = a.y * b.z - a.z * b.y;
    result.y = a.z * b.x - a.x * b.z;
    result.z = a.x * b.y - a.y * b.x;
    return result;
}

double magnitude(struct Vector3D v) {
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

void print_vector(struct Vector3D v) {
    printf("%s = (%.2f, %.2f, %.2f)\n", v.name, v.x, v.y, v.z);
}

int main(void) {
    struct Vector3D A = {"A", 1.0, 2.0, 3.0};
    struct Vector3D B = {"B", 4.0, 5.0, 6.0};

    print_vector(A);
    print_vector(B);

    printf("Скалярное произведение: %.2f\n", dot_product(A, B));

    struct Vector3D C = cross_product(A, B, "C");
    print_vector(C);

    printf("Модуль вектора %s: %.2f\n", A.name, magnitude(A));
    printf("Модуль вектора %s: %.2f\n", B.name, magnitude(B));

    return 0;
}