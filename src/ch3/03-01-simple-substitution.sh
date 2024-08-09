#!/bin/bash

# I retrieved Cory Doctorow's novel Little Brother from
# https://craphound.com/littlebrother/Cory_Doctorow_-_Little_Brother.txt

# Snip off end (starting at original line 6355)
head –n 6355 littlebrother.txt > lb_edit.txt

# Snip off introduction & creative commons stuff (first 251 lines)
tail -n +251 lb_edit.txt > lb_edit2.txt

# This still has some commentary, but that’s ok

# Now get rid of punctuation with “translate” command:
tr -cd [:alpha:] < lb_edit2.txt> lb_edit3.txt

# Convert all uppercase to lowercase
tr [:upper:] [:lower:] < lb_edit3.txt > lb_edit4.txt

# Now apply ROT13 to lb_edit4.txt
tr a-z n-za-m <lb_edit4.txt >lb_rot13.txt

# And do some frequency analysis on the rotated file by putting each remaining letter
# on a line of its own, sort it, count the number of each, sort by most frequent
grep -o . lb_rot13.txt | sort | uniq -c | sort -n -r > frequency_rot13.txt

# Now do the same for the unencrypted version for comparison
grep -o . lb_edit4.txt | sort | uniq -c | sort -n -r > frequency.txt
