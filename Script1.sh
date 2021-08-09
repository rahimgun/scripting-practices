#!/bin/bash

echo Enter a string:

read word

files=($(find . -name "*.txt"))
numberOfFiles=${#files[@]}

mkdir -p Matches

i=0

while [ $i -lt $numberOfFiles ]
do
	count=$(grep -wo $word ${files[i]} | wc -l)
	if [ $count -ne 0 ]
	then
		temp=${files[i]}
		mv ${files[i]} ./Matches/${temp%.*}_$count.txt
	fi
	i=$((i+1))
done
