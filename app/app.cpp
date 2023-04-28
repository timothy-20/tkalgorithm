//
// Created by aircuve on 2023-03-21.
//

#include <iostream>
#include <complex>
#include <vector>
#include <cmath>

static double const PI = acos(-1);

std::vector<std::complex<double>> dft(std::vector<double> const& x) {
    size_t N(x.size());
    std::vector<std::complex<double>> X(N);

    for (int i(0); i < N; i++) {
        for (int j(0); j < N; j++) {
            double real(x[j] * cos(2 * PI * i * j / N));
            double imag(-x[j] * sin(2 * PI * i * j / N));
            X[i] += std::complex<double>(real, imag);
        }
    }

    return X;
}

int main() {

    return 0;
}
