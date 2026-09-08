#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

#define PI 3.14159265358979323846

void fft(double complex *a, int n, int invert) {
    if (n == 1) return;

    double complex *a_even = malloc((n / 2) * sizeof(double complex));
    double complex *a_odd = malloc((n / 2) * sizeof(double complex));

    for (int i = 0; 2 * i < n; i++) {
        a_even[i] = a[2 * i];
        a_odd[i] = a[2 * i + 1];
    }

    fft(a_even, n / 2, invert);
    fft(a_odd, n / 2, invert);

    double angle = 2 * PI / n * (invert ? -1 : 1);
    double complex w = 1.0 + 0.0 * I;
    double complex wn = cos(angle) + sin(angle) * I;

    for (int i = 0; 2 * i < n; i++) {
        double complex t = w * a_odd[i];
        a[i] = a_even[i] + t;
        a[i + n / 2] = a_even[i] - t;
        if (invert) {
            a[i] /= 2;
            a[i + n / 2] /= 2;
        }
        w *= wn;
    }

    free(a_even);
    free(a_odd);
}

void convolve(double *A, int m, double *B, int n, double *C) {
    int N = 1;
    while (N < m + n - 1) N <<= 1;

    double complex *fa = calloc(N, sizeof(double complex));
    double complex *fb = calloc(N, sizeof(double complex));

    for (int i = 0; i < m; i++) fa[i] = A[i];
    for (int i = 0; i < n; i++) fb[i] = B[i];

    fft(fa, N, 0);
    fft(fb, N, 0);

    for (int i = 0; i < N; i++) fa[i] *= fb[i];

    fft(fa, N, 1);

    for (int i = 0; i < m + n - 1; i++) C[i] = creal(fa[i]);

    free(fa);
    free(fb);
}

int main() {
    int m = 3, n = 4;
    double A[] = {1.0, 2.0, 3.0};
    double B[] = {4.0, 5.0, 6.0, 7.0};
    double *C = malloc((m + n - 1) * sizeof(double));

    convolve(A, m, B, n, C);

    for (int i = 0; i < m + n - 1; i++) {
        printf("C[%d] = %.2f\n", i, C[i]);
    }

    free(C);
    return 0;
}
