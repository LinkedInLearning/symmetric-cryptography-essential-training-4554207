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

// Note that this code must be compiled with C++11 support.
#include <iostream>
#include <cstdint>
#include <bitset>

using namespace std;

void printInt(uint8_t* ptr, uint8_t len, bool littleEnd = true)
{
    if (littleEnd) // Assume we want to print as little-endian
    {
        // Take each byte and print it out in binary format
        for (int8_t i = 0; i < len; i++)
        {
            cout << bitset<8>(*(ptr + i)) << ' ';
        }
    }
    else // If function called with littleEnd = false, print as
    {    // big-endian
        for (int8_t i = len - 1; i >= 0; i--)
        {
            cout << bitset<8>(*(ptr + i)) << ' ';
        }
    }

    cout << '\n';
}

int main()
{
    // 8-bit/1-byte integers
    int8_t a;
    uint8_t b;

    // 16-bit/2-byte integers
    int16_t c;
    uint16_t d;

    // 32-bit/4-byte integers
    int32_t e;
    uint32_t f;

    // 64-bit/8-byte integers
    int64_t g;
    uint64_t h;

    // Set 1-byte integers a and b to 17
    a = 17;
    b = 17;

    cout << "a = ";
    printInt((uint8_t*)&a, sizeof(a));

    cout << "b = ";
    printInt((uint8_t*)&b, sizeof(b));

    // Now set a to a negative number
    a = -17;
    cout << "a = ";
    printInt((uint8_t*)&a, sizeof(a));

    c = 258;
    d = 258;
    cout << "\nc = ";
    printInt((uint8_t*)&c, sizeof(c));
    cout << "BE= ";
    printInt((uint8_t*)&c, sizeof(c), false);

    cout << "d = ";
    printInt((uint8_t*)&d, sizeof(d));

    c = -258;
    cout << "c = ";
    printInt((uint8_t*)&c, sizeof(c));



    e = 65539;
    f = 65539;
    cout << "\ne = ";
    printInt((uint8_t*)&e, sizeof(e));

    cout << "f = ";
    printInt((uint8_t*)&f, sizeof(f), false);

    e = -65539;
    cout << "e = ";
    printInt((uint8_t*)&e, sizeof(e));




    g = 65539;
    g <<= 16;
    h = 65539;
    h <<= 16;
    cout << "\ng = ";
    printInt((uint8_t*)&g, sizeof(g));

    cout << "h = ";
    printInt((uint8_t*)&h, sizeof(h), false);

    cout << "Integer value = " << g << '\n';

    g = -g;
    cout << "Integer value = " << g << '\n';

    cout << "g = ";
    printInt((uint8_t*)&g, sizeof(g));


    return 0;
}
