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
 *
 */

#include <cstdint>
#include <iostream>

using namespace std;

void printIntegerGrid(uint64_t input) {

  for (int i = 0; i < 64; i++) {
    if ((input & (1ULL << (63 - i))) != 0ULL) {
      cout << '*';
    } else {
      cout << '_';
    }


    if ((i % 8) == 7) {
      cout << '\n';
    }
  }

  return;
}

int main() {  
  uint64_t userInput;
  uint64_t zeroTest = 0;
  uint64_t randomTest = 12133653013031549986U; // The u forces it to be unsigned

  cout << "Type a number to display: ";
  cin >> userInput;
  
  cout << "\nHere's a zero grid:\n";
  printIntegerGrid(zeroTest);

  cout << "\nHere's a 'random' grid:\n";
  printIntegerGrid(randomTest);

  cout << "\nHere's your number's grid:\n";
  printIntegerGrid(userInput);

  return 0;
}