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
#include <cstring>

using namespace std;

// We're assuming (insecurely) that there is enough space in the array to add padding
// Return the number of bytes padded
// FOR DEMONSTRATION ONLY--PLEASE DO NOT USE THIS IN REAL CODE
uint8_t padPKCS7(uint8_t* ptr, uint16_t msgLen, uint8_t blockSize)
{
    uint8_t leftover = msgLen % blockSize; // divide msgLen by blockSize & keep remainder
    uint8_t toPad = blockSize - leftover;

    // If the message falls nicely on a block boundary, pad out one more full block
    if (toPad == 0)
        toPad = 8;

    for (int8_t i = 0; i < toPad; i++)
    {
        ptr[msgLen + i] = toPad;
    }

    return toPad;
}


// We're assuming (insecurely) that there is enough space in the array to add padding
// Return the number of bytes padded
// FOR DEMONSTRATION ONLY--PLEASE DO NOT USE THIS IN REAL CODE
uint8_t padX923(uint8_t* ptr, uint16_t msgLen, uint8_t blockSize)
{
    uint8_t leftover = msgLen % blockSize; // divide msgLen by blockSize & keep remainder
    uint8_t toPad = blockSize - leftover;

    // If the message falls nicely on a block boundary, pad out one more full block
    if (toPad == 0)
        toPad = 8;

    for (int8_t i = 0; i < (toPad - 1); i++)
    {
        ptr[msgLen + i] = 0x0;
    }
    ptr[msgLen + (toPad - 1)] = toPad; // Now add how many bytes we padded

    return toPad;
}


// We're assuming (insecurely) that there is enough space in the array to add padding
// Return the number of bytes padded
// FOR DEMONSTRATION ONLY--PLEASE DO NOT USE THIS IN REAL CODE
uint8_t bitPadding(uint8_t* ptr, uint16_t msgLen, uint8_t blockSize)
{
    uint8_t leftover = (msgLen + 1) % blockSize; // divide msgLen by blockSize + 1 & keep remainder
    // (we add the + 1 to account for the initial 0x80 byte)
    uint8_t toPad = blockSize - leftover;

    // Add our initial 0x80 byte
    ptr[msgLen] = 0x80;

    // If the message (with the block added so far) falls nicely on a block boundary, pad out one more full block
    if (toPad == 0)
        toPad = 8;

    for (int8_t i = 0; i < toPad; i++)
    {
        ptr[msgLen + 1 + i] = 0x0;
    }

    return toPad + 1;
}



void printArray(uint8_t* ptr, uint16_t len)
{
     // Take each byte and print it out in binary format
    for (int16_t i = 0; i < len; i++)
    {
        cout << bitset<8>(*(ptr + i)) << ' ';

        if (i % 8 == 7)
            cout << '\n';
    }
    cout << '\n';
}

int main()
{
    const uint8_t blockSize = 8;
    const uint8_t arraySize = 32;
    uint8_t inputArray[arraySize];
    uint8_t bitPadArray[arraySize];
    uint8_t x923Array[arraySize];
    uint8_t pkcs7Array[arraySize];

    uint16_t msgLength;

    for (uint16_t i = 0; i < arraySize; i++)
    {
        // Just to demonstrate where the unused bytes are
        inputArray[i] = 0xff;
    }

    cout << "Type something: ";
    cin >> inputArray;

    cout << "Original array: \n";
    printArray(inputArray, arraySize);

    // Not safe
    msgLength = strlen((char*)inputArray);

    // Make three copies of the input array
    for (uint16_t i = 0; i < arraySize; i++)
    {
        bitPadArray[i] = inputArray[i];
        x923Array[i] = inputArray[i];
        pkcs7Array[i] = inputArray[i];
    }

    padPKCS7(pkcs7Array, msgLength, blockSize);
    bitPadding(bitPadArray, msgLength, blockSize);
    padX923(x923Array, msgLength, blockSize);

    cout << "\nBit padding:\n";
    printArray(bitPadArray, arraySize);

    cout << "\nPKCS#7 padding:\n";
    printArray(pkcs7Array, arraySize);

    cout << "\nX.923 padding:\n";
    printArray(x923Array, arraySize);


    return 0;
}
