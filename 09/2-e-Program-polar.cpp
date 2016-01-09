// Copyright © 2016 Martin Ueding <dev@martin-ueding.de>

#include <cmath>
#include <iostream>
#include <random>

struct vec {
    double x, y, z;

    double norm() const { return std::sqrt(x * x + y * y + z * z); }

    vec operator+(const vec &other) const {
        return {x + other.x, y + other.y, z + other.z};
    }

    vec operator-(const vec &other) const {
        return {x - other.x, y - other.y, z - other.z};
    }

    vec operator/(const double q) const { return {x / q, y / q, z / q}; }
};

double integrate(const long runs) {
    std::default_random_engine re;
    std::uniform_real_distribution<double> dist1(-1, 1);
    std::uniform_real_distribution<double> dist2(0, 2);

    const auto r1 = [&re, &dist1] { return dist1(re); };
    const auto r2 = [&re, &dist2] { return dist2(re); };

    double integral = 0.0;
    const double box_size = std::pow(2, 3) * std::pow(2, 1);

    for (auto run = 0L; run <= runs; ++run) {
        const vec p = {r1(), r1(), r1()};
        const vec q = {r2(), 0, 0};

        const auto norm_plus = (p + q / 2).norm();
        const auto norm_minus = (p - q / 2).norm();

        if (norm_plus < 1 && norm_minus < 1) {
            integral += 1;
        }
    }

    const auto result = integral * box_size / runs;

    return result;
}

int main(int argc, char **argv) {
    for (int power = 3; power != 9; ++power) {
        const long runs = std::pow(10, power);
        const auto integral = integrate(runs);
        std::cout << "10^" << power << ":\t" << integral << std::endl;
    }

    return 0;
}
