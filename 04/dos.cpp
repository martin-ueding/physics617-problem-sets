// Copyright © 2015 Martin Ueding <dev@martin-ueding.de>

#include <iostream>
#include <cmath>

double dispersion(double k_x, double k_y) {
    return std::sqrt(2 - std::cos(k_x) - std::cos(k_y));
}

int main(int argc, char **argv) {
    return 0;
}
