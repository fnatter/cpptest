#!/bin/sh

make Alignment
./Alignment ACTTTATGCCTGCT ACAGGCT 1 -1 -2
./Alignment ACTTTATGCCTGCT ACAGGCT 1 -1 -2 freegapstart1,freegapend1,freegapstart2,freegapend2

