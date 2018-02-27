#!/bin/sh

make Alignment
#./Alignment NP_000913.fasta NP_002590.fasta 2 -1 -1
# => score -162
#./Alignment NP_000913.fasta NP_246273.fasta 2 -1 -1
# => score -227
./Alignment NP_002590.fasta NP_246273.fasta 2 -1 -1
# => score -14

#NP_000913.fasta                    
#NP_002590.fasta
#NP_246273.fasta
