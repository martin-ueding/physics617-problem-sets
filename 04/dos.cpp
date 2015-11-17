// Copyright © 2015 Martin Ueding <dev@martin-ueding.de>

#include <cmath>
#include <fstream>
#include <vector>

size_t get_bin(const double value,
               const size_t bin_count,
               const double min,
               const double max) {
    const auto offset = value - min;
    const auto ratio = offset / (max - min);
    return ratio * (bin_count);
}

double get_energy(const double k_x, const double k_y) {
    return std::sqrt(2 - std::cos(k_x) - std::cos(k_y));
}

int main(const int argc, const char * const * const argv) {
    const auto pi = std::atan(1) * 4;

    const auto bin_count = 1000;
    const auto bin_width = 2.0 / bin_count;
    std::vector<int> histogram(bin_count, 0);

    const auto step_count = 10000;
    const auto spacing = pi / step_count;

    for (int i = 0; i < step_count; ++i) {
        for (int j = 0; j < step_count; ++j) {
            const auto energy = get_energy(i * spacing, j * spacing);
            ++histogram[get_bin(energy, bin_count, 0, 2)];
        }
    }

    std::ofstream out{"dos-cpp.txt"};
    for (int i = 0; i != histogram.size(); ++i) {
        out << (i * 2.0 / histogram.size()) << "\t"
            << static_cast<double>(histogram[i]) / (step_count * step_count) /
                   bin_width << "\n";
    }

    return 0;
}
