/*
 * Copyright (c) 2024, Jeremy A. Hansen. All rights reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * This code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 3, as
 * published by the Free Software Foundation.
 *
 * This code is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * version 3 (https://www.gnu.org/licenses/gpl-3.0.txt) for more details.
 *
 */

#include <iostream>
#include <random>

using namespace std;

int main()
{
    const uint64_t m = 13, g = 7;
    uint64_t privateA = 0, privateB = 0, publicA = 0, publicB = 0;
    uint64_t sharedA = 0, sharedB = 0;

    // Lots of decent ways to generate random numbers, but this one is straightforward

    // Setting up random source--we get good non-deterministic randomness from this!
    // https://en.cppreference.com/w/cpp/numeric/random/random_device
    random_device rd;
    mt19937 eng(rd());

    // Choose a number between 3 and 12
    uniform_int_distribution<int> uniform_dist(3, 12);
    privateA = uniform_dist(eng);
    privateB = uniform_dist(eng);

    //cout << "privateA = " << privateA << endl;
    //cout << "privateB = " << privateB << endl;

    publicA = (uint64_t)pow(g, privateA) % m;
    publicB = (uint64_t)pow(g, privateB) % m;

    //cout << "publicA = " << publicA << endl;
    //cout << "publicB = " << publicB << endl;

    sharedA = (uint64_t)pow(publicB, privateA) % m;
    sharedB = (uint64_t)pow(publicA, privateB) % m;

    cout << "Alice's secret: " << sharedA << endl;
    cout << "Bob's secret:   " << sharedB << endl;

    if (sharedA == sharedB) {
        cout << "Yay! They match!" << endl;
    }

    return 0;
}
