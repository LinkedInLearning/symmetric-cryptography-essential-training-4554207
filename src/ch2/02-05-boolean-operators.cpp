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
    uint8_t a, b, c;

    // 32-bit/4-byte integers
    uint32_t d, e, f;

    a = 0b01010101; // 170
    b = 0b11110000; // 240

    cout << "      a = ";
    printInt((uint8_t*)&a, sizeof(a));

    cout << "      b = ";
    printInt((uint8_t*)&b, sizeof(b));

    cout << "a AND b = ";
    c = a & b;
    printInt((uint8_t*)&c, sizeof(c));


    cout << "\n      a = ";
    printInt((uint8_t*)&a, sizeof(a));

    cout << "      b = ";
    printInt((uint8_t*)&b, sizeof(b));

    cout << "a  OR b = ";
    c = a | b;
    printInt((uint8_t*)&c, sizeof(c));


    cout << "\n      a = ";
    printInt((uint8_t*)&a, sizeof(a));

    cout << "      b = ";
    printInt((uint8_t*)&b, sizeof(b));

    cout << "a XOR b = ";
    c = a ^ b;
    printInt((uint8_t*)&c, sizeof(c));


    cout << "\n      a = ";
    printInt((uint8_t*)&a, sizeof(a));

    c = ~a;
    cout << "  NOT a = ";
    printInt((uint8_t*)&c, sizeof(c));


    d = 0b01010101110011001100001100000000;
    e = 0b11110000111111110000111111110000;

    cout << "------------------";
    cout << "\n      d = ";
    printInt((uint8_t*)&d, sizeof(d));

    cout << "      e = ";
    printInt((uint8_t*)&e, sizeof(e));

    cout << "d AND e = ";
    f = d & e;
    printInt((uint8_t*)&f, sizeof(f));


    cout << "\n      d = ";
    printInt((uint8_t*)&d, sizeof(d));

    cout << "      e = ";
    printInt((uint8_t*)&e, sizeof(e));

    cout << "d  OR e = ";
    f = d | e;
    printInt((uint8_t*)&f, sizeof(f));



    cout << "\n      d = ";
    printInt((uint8_t*)&d, sizeof(d));

    cout << "      e = ";
    printInt((uint8_t*)&e, sizeof(e));

    cout << "d XOR e = ";
    f = d ^ e;
    printInt((uint8_t*)&f, sizeof(f));


    cout << "\n      d = ";
    printInt((uint8_t*)&d, sizeof(d));

    f = ~d;
    cout << "  NOT d = ";
    printInt((uint8_t*)&f, sizeof(f));


    return 0;
}
