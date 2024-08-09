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

using namespace std;

void caesar(char plain[64], char cipher[64], unsigned int key)
{
    int index = 0;
    unsigned char temp;
    // Keep going until the end of the string
    while (plain[index] != '\0')
    {
        // lowercase letters
        if (plain[index] >= 'a' && plain[index] <= 'z')
        {
            temp = plain[index] + key;

            if (temp > 'z')
                cipher[index] = temp - 26;
            else
                cipher[index] = temp;
        }
        // capital letters
        else if (plain[index] >= 'A' && plain[index] <= 'Z')
        {
            cipher[index] = plain[index] + key;
            temp = plain[index] + key;

            if (temp > 'Z')
                cipher[index] = temp - 26;
            else
                cipher[index] = temp;
        }
        // everything else that's not a letter is left unchanged
        else
            cipher[index] = plain[index];
        index++;
    }
    cipher[index] = '\0';

}

int main()
{
    char myInput[64];
    char ciphertext[64];
    char candidate[64];
    unsigned int myKey;
    char brute;

    cout << "Enter a string: ";
    cin.getline(myInput, 64);

    cout << "Your key, a number between 1 and 25: ";
    cin >> myKey;
    // Should have error checking here. Left out for readability

    caesar(myInput, ciphertext, myKey);

    cout << "\nThe same string, with your key:\n" << ciphertext;

    cout << "\n\nFind the original message with brute force (y/n)? ";

    cin >> brute;

    if (brute != 'y' && brute != 'Y')
        return 0;

    for (unsigned int curKey = 1; curKey < 26; curKey++)
    {
        caesar(ciphertext, candidate, curKey);
        cout.width(2);
        cout << curKey << ": " << candidate << '\n';
    }

    return 0;
}
