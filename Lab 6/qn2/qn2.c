#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

void add_matrices(double *A, double *B, double *C, int n) {
    for (int i = 0; i < n * n; i++) C[i] = A[i] + B[i];
}

void multiply_matrices(double *A, double *B, double *C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i * n + j] = 0;
            for (int k = 0; k < n; k++) C[i * n + j] += A[i * n + k] * B[k * n + j];
        }
    }
}

bool is_zero_matrix(double *A, int n) {
    for (int i = 0; i < n * n; i++) if (A[i] != 0.0) return false;
    return true;
}

bool is_symmetric(double *A, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) if (A[i * n + j] != A[j * n + i]) return false;
    }
    return true;
}

double calculate_determinant(double *A, int n) {
    double *temp = malloc(n * n * sizeof(double));
    for (int i = 0; i < n * n; i++) temp[i] = A[i];
    double det = 1.0;

    for (int i = 0; i < n; i++) {
        int pivot = i;
        for (int j = i + 1; j < n; j++) if (fabs(temp[j * n + i]) > fabs(temp[pivot * n + i])) pivot = j;
        if (pivot != i) {
            for (int k = 0; k < n; k++) {
                double t = temp[i * n + k];
                temp[i * n + k] = temp[pivot * n + k];
                temp[pivot * n + k] = t;
            }
            det *= -1.0;
        }
        if (temp[i * n + i] == 0.0) { free(temp); return 0.0; }
        det *= temp[i * n + i];
        for (int j = i + 1; j < n; j++) {
            double factor = temp[j * n + i] / temp[i * n + i];
            for (int k = i; k < n; k++) temp[j * n + k] -= factor * temp[i * n + k];
        }
    }
    free(temp); return det;
}

void transpose_in_place(double *A, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double temp = A[i * n + j];
            A[i * n + j] = A[j * n + i];
            A[j * n + i] = temp;
        }
    }
}

void power_iteration_eigen(double *A, int n, double *eigenvector, double *eigenvalue) {
    for (int i = 0; i < n; i++) eigenvector[i] = 1.0;
    double *next_vec = malloc(n * sizeof(double));

    for (int iter = 0; iter < 100; iter++) {
        for (int i = 0; i < n; i++) {
            next_vec[i] = 0;
            for (int j = 0; j < n; j++) next_vec[i] += A[i * n + j] * eigenvector[j];
        }
        double norm = 0;
        for (int i = 0; i < n; i++) norm += next_vec[i] * next_vec[i];
        norm = sqrt(norm);
        for (int i = 0; i < n; i++) eigenvector[i] = next_vec[i] / norm;
    }
    double num = 0, den = 0;
    for (int i = 0; i < n; i++) {
        double Ax = 0;
        for (int j = 0; j < n; j++) Ax += A[i * n + j] * eigenvector[j];
        num += eigenvector[i] * Ax; den += eigenvector[i] * eigenvector[i];
    }
    *eigenvalue = num / den; free(next_vec);
}

int main() {
    int n = 3;
    double *A = malloc(n * n * sizeof(double));
    double *B = malloc(n * n * sizeof(double));
    double *C = malloc(n * n * sizeof(double));
    double dataA[] = {4, 1, 1, 1, 3, 0, 1, 0, 2};
    double dataB[] = {1, 0, 0, 0, 1, 0, 0, 0, 1};

    for (int i = 0; i < n * n; i++) { A[i] = dataA[i]; B[i] = dataB[i]; }

    add_matrices(A, B, C, n);
    multiply_matrices(A, B, C, n);
    bool zero = is_zero_matrix(A, n);
    bool sym = is_symmetric(A, n);
    double det = calculate_determinant(A, n);
    transpose_in_place(A, n);
    
    double *vec = malloc(n * sizeof(double)), val;
    power_iteration_eigen(A, n, vec, &val);

    printf("Det: %.2f | Eigenval: %.2f\n", det, val);
    free(A); free(B); free(C); free(vec);
    return 0;
}
