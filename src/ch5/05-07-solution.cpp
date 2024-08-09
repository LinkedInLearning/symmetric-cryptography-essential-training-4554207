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
#include <fstream>

using namespace std;

uint64_t MyRound(uint64_t input, uint64_t key);
char* MyEncrypt(char* plaintext, uint32_t fileLen, uint64_t key, uint64_t iv);

int main()
{
    //ifstream inFile("plaintext.txt", ifstream::binary);
    //uint32_t fileLength = 0;

    ofstream outFile("ciphertext.txt", ofstream::binary);
    char *plaintext, *ciphertext;
    uint64_t key = 0x945c5a496f864851;
    uint64_t iv = 0x49cef0abf4d98498;

    //if (!inFile) {
    //  cout << "Bad input file!" << endl;
    //  return -1;
    //}
    // Get the length of the file
    //inFile.seekg(0, inFile.end);
    //fileLength = inFile.tellg();
    //inFile.seekg(0, inFile.beg);

    // Allocate space in memory for the file contents
    //plaintext = new char[fileLength];

    // Copy the file contents into memory
    //inFile.read(plaintext, fileLength);
    //inFile.close();

    ciphertext = MyEncrypt("QUITE THE SITUATION HERE", 24, key, iv);

    // Put the resulting ciphertext into the file
    outFile.write(ciphertext, 24);
    outFile.close();

    //delete[] plaintext;
    delete[] ciphertext;

    return 0;
}

uint64_t MyRound(uint64_t input, uint64_t key) {
    // Skipping expansion and going straight for the XOR with the key
    input ^= key;
    uint32_t r = (uint32_t)input; // grab right 32 bits
    uint32_t l = input >> 32; // left 32 bits
    uint32_t rOut, lOut;
    unsigned char a, b, c, d, aa, bb, cc, dd;
    unsigned char sbox1[256] =
    { 216, 81, 103, 180, 243, 218, 234, 20, 136, 137, 93, 115, 107, 155,
    206, 56, 52, 236, 165, 99, 173, 129, 199, 164, 131, 135, 148, 213,
    196, 158, 217, 207, 9, 252, 172, 232, 174, 94, 116, 15, 48, 150, 28,
    4, 49, 177, 197, 225, 34, 212, 59, 239, 42, 74, 88, 29, 250, 235, 233,
    64, 69, 114, 85, 80, 124, 133, 205, 169, 193, 97, 21, 24, 211, 152,
    184, 84, 120, 162, 226, 255, 95, 153, 161, 249, 214, 198, 66, 149,
    128, 101, 200, 190, 176, 23, 237, 142, 86, 50, 132, 31, 110, 117,
    223, 89, 220, 40, 240, 53, 12, 36, 254, 96, 229, 65, 242, 157, 209,
    76, 35, 75, 145, 16, 13, 245, 45, 46, 33, 122, 159, 125, 30, 87, 194,
    151, 248, 19, 166, 10, 163, 246, 134, 77, 72, 17, 60, 79, 8, 175, 68,
    26, 39, 185, 32, 138, 222, 2, 55, 143, 25, 188, 51, 181, 238, 118, 27,
    57, 147, 43, 167, 98, 139, 121, 130, 144, 215, 106, 47, 11, 105, 73,
    183, 241, 91, 204, 187, 78, 100, 54, 108, 182, 123, 104, 202, 228, 58,
    113, 253, 126, 6, 168, 82, 102, 189, 63, 227, 247, 208, 231, 112, 140,
    210, 83, 0, 1, 171, 90, 22, 146, 230, 179, 71, 154, 191, 195, 156, 201,
    244, 186, 67, 41, 109, 224, 92, 7, 38, 111, 192, 221, 160, 141, 44, 3,
    203, 170, 61, 37, 14, 18, 119, 5, 62, 127, 178, 219, 251, 70 };
    unsigned char sbox2[256] =
    { 80, 130, 100, 198, 141, 153, 248, 137, 127, 66, 243, 85, 226, 185,
    222, 2, 121, 111, 73, 36, 102, 35, 168, 89, 5, 7, 159, 246, 136, 32,
    76, 203, 101, 33, 233, 54, 3, 129, 206, 196, 87, 237, 21, 49, 116, 55,
    193, 117, 90, 82, 165, 12, 56, 113, 247, 40, 106, 150, 213, 215, 19,
    75, 178, 37, 88, 239, 138, 225, 188, 209, 140, 105, 228, 234, 42, 30,
    174, 52, 161, 51, 227, 170, 126, 118, 163, 4, 214, 171, 158, 195, 48,
    205, 20, 143, 43, 26, 18, 223, 182, 249, 98, 220, 65, 160, 128, 255,
    39, 146, 191, 17, 245, 50, 204, 64, 212, 120, 242, 81, 229, 232, 27,
    254, 186, 183, 148, 110, 9, 83, 109, 224, 86, 250, 142, 194, 16, 240,
    6, 202, 144, 114, 189, 177, 231, 70, 151, 238, 31, 241, 34, 14, 77, 57,
    92, 184, 10, 167, 181, 123, 8, 59, 84, 28, 58, 162, 44, 147, 11, 25,
    71, 79, 235, 149, 218, 74, 97, 61, 124, 211, 104, 95, 135, 134, 154,
    251, 41, 236, 46, 190, 199, 200, 173, 152, 60, 207, 22, 187, 208, 69,
    24, 47, 180, 91, 72, 219, 201, 0, 145, 122, 169, 221, 99, 53, 133, 217,
    45, 197, 156, 112, 175, 253, 67, 157, 107, 108, 68, 244, 1, 164, 115,
    93, 166, 210, 29, 119, 15, 38, 94, 62, 252, 63, 230, 125, 155, 179,
    216, 103, 131, 192, 176, 139, 78, 96, 13, 172, 132, 23 };

    // Break up R into 4 separate bytes
    aa = (unsigned char)(r >> 24);
    bb = (unsigned char)((r & 0x00ffffff) >> 16);
    cc = (unsigned char)((r & 0x0000ffff) >> 8);
    dd = (unsigned char)r;

    // Apply S-Boxes
    a = sbox1[cc];
    b = sbox2[sbox1[aa]];
    c = sbox1[sbox2[dd]];
    d = sbox2[bb];

    // Reconstruct 32-bit R
    rOut = ((uint32_t)a << 24) + ((uint32_t)b << 16) + ((uint32_t)c << 8) + d;

    // Not applying P-Boxes in this function

    // XORing the result with the previous L
    rOut ^= l;

    lOut = r;

    return ((uint64_t)lOut << 32) + rOut;
}

char* MyEncrypt(char* plaintext, uint32_t inputLen, uint64_t key, uint64_t iv) {
    unsigned int currentPos = 0;
    unsigned int currentBlock = 0;
    uint64_t currentInput;
    // Must allocate space and return a pointer to the encrypted message
    char* ciphertext = new char[inputLen];

    // copy IV into the currentInput
    currentInput = iv;

    // Skipping for now: we would add padding here

    // The big for loop here
    for (uint32_t i = 0; i < inputLen; i += 8) {
        // XOR message block with IV (1st) or previous round (all the rest)
        currentInput = (*(uint64_t*)(plaintext + i)) ^ currentInput;

        // Now use the block cipher
        currentInput = MyRound(currentInput, key);

        // Copy the currentInput into the ciphertext 
        *(uint64_t*)(ciphertext + i) = currentInput;
    }

    return ciphertext;
}

