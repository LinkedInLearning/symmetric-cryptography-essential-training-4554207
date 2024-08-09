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

// FOR DEMONSTRATION ONLY--PLEASE DO NOT USE THIS IN REAL CODE

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
    uint16_t index = 0;
    char plaintext[256];
    char plaintextOut[256];
    uint8_t ciphertext[256];
    // Random bytes courtesy of random.org
    uint8_t randomKey[256] = {
        249, 3, 141, 247, 131, 159, 178, 248, 235, 96,
        85, 238, 12, 156, 41, 218, 107, 219, 112, 199,
        191, 128, 239, 146, 29, 28, 20, 18, 250, 226,
        94, 121, 119, 37, 237, 50, 193, 250, 132, 240,
        123, 131, 91, 109, 10, 5, 145, 170, 160, 140,
        156, 41, 120, 61, 115, 108, 253, 85, 181, 74,
        128, 16, 163, 201, 125, 191, 38, 102, 94, 66,
        101, 128, 233, 190, 179, 23, 170, 144, 71, 170,
        115, 161, 108, 202, 10, 164, 112, 246, 232, 223,
        170, 184, 239, 200, 22, 91, 129, 235, 25, 200,
        20, 153, 210, 178, 228, 158, 141, 105, 88, 206,
        174, 19, 89, 252, 210, 10, 22, 202, 103, 109,
        193, 76, 38, 170, 135, 165, 103, 105, 138, 219,
        22, 218, 130, 84, 104, 196, 222, 202, 39, 36,
        150, 228, 246, 159, 243, 137, 25, 145, 208, 80,
        153, 129, 14, 66, 203, 120, 74, 232, 228, 237,
        134, 37, 102, 179, 226, 187, 18, 182, 214, 48,
        154, 31, 54, 12, 170, 229, 149, 26, 10, 44,
        201, 193, 67, 194, 38, 186, 62, 87, 107, 118,
        209, 166, 239, 68, 218, 63, 22, 230, 127, 159,
        179, 79, 220, 40, 217, 37, 199, 55, 208, 86,
        120, 178, 233, 110, 215, 212, 91, 39, 69, 251,
        247, 157, 74, 211, 148, 212, 168, 87, 84, 182,
        103, 12, 125, 14, 66, 125, 108, 98, 233, 220,
        107, 101, 78, 199, 231, 81, 156, 41, 221, 16,
        69, 133, 101, 50, 34, 37
    };

    cout << "Enter your message: \n";
    cin.getline(plaintext, 256);

    // XOR each byte of the plaintext with the key material
    // to produce the ciphertext
    while(plaintext[index] != '\0')
    {
        ciphertext[index] = plaintext[index] ^ randomKey[index]; 
        index++;
    }

    // Using index as length
    for (int j = 0; j < index; j++)
    {
        cout << ciphertext[j];
    }

    cout << "\n\nFirst 8 bytes in binary\n plain: ";
    printInt((uint8_t*)plaintext, 8);
    cout << "   key: ";
    printInt(randomKey, 8);
    cout << "cipher: ";
    printInt(ciphertext, 8);

    cout << "\n\nCalculating original plaintext:\n";

    // XOR each byte of the ciphertext with the key material
    // to produce the plaintext
    for (int j = 0; j < index; j++)
    {
        plaintextOut[j] = ciphertext[j] ^ randomKey[j];
        cout << plaintextOut[j];
    }

    return 0;
}
