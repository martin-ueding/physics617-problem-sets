#!/usr/bin/python3
# -*- coding: utf-8 -*-

# Copyright © 2015 Martin Ueding <dev@martin-ueding.de>

import argparse
import numpy as np
import scipy.integrate


def get_energy(k_x, k_y):
    return np.sqrt(2 - np.cos(k_x) - np.cos(k_y))


def main():
    options = _parse_args()

    pillars = 1000

    lin = np.linspace(0, np.pi, pillars) 
    k_x = np.tile(lin, (pillars, 1))
    k_y = np.tile(lin, (pillars, 1)).transpose()

    energies = get_energy(k_x, k_y)

    counts, bins = np.histogram(energies, bins=100)
    width = bins[1] - bins[0]
    y = counts / pillars**2 / width
    np.savetxt('dos-py.txt', np.column_stack([bins[:-1], y]))

    integral = scipy.integrate.simps(y, bins[:-1])
    print(integral)


def _parse_args():
    parser = argparse.ArgumentParser(description='')
    options = parser.parse_args()

    return options


if __name__ == '__main__':
    main()
