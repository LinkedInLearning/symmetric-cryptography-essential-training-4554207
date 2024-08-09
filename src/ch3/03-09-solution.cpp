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

#include <cstdint>
#include <iostream>

using namespace std;

int main() {  
  //              V-----------------------------+-----+--+-----+
  int lfsr[16] = {0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0};
  int newBit;

  // Iterate the LFSR 35 times and print its output to the screen
  // The new value entering from the left into position lfsr[0]
  // should be an XOR of bits at positions 10, 12, 13, 15
  // Print the values that "fall out" of the register

  for (int i = 0; i < 35; i++) {
    cout << lfsr[15] << ' ';
    newBit = lfsr[10] ^ lfsr[12] ^ lfsr[13] ^ lfsr[15];

    for (int j = 15; j > 0; j--) {
      lfsr[j] = lfsr[j - 1];
    }

    lfsr[0] = newBit;
  }

  cout << "\nState of the LFSR at the end:\n";

  for (int i = 0; i < 16; i++) {
    cout << lfsr[i] << ", ";
  }
  cout << '\n';

  return 0;
}