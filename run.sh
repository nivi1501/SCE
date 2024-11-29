#!/bin/bash

# Clean previous builds
echo "Cleaning previous builds..."
make clean

# Compile and execute main_time
echo "Building and running main_time..."
make
./main_time | tee main_time_output.txt

# Extract time taken from main_time
echo "Extracting time from main_time output..."
main_time_taken=$(grep "Time taken" main_time_output.txt | awk '{print $3}')
echo "Time taken by SCE algorithm: ${main_time_taken} ms"


# Compile and execute AES
echo "Compiling aes..."
make -f Makefile.aes


echo "Running aes..."
./aes | tee aes_output.txt

# Extract time taken from aes
echo "Extracting time from aes output..."
aes_time_taken=$(grep "Time taken" aes_output.txt | awk '{print $3}')
echo "Time taken by aes: ${aes_time_taken} ms"

# Compare timings
echo "=================== Timing Comparison ==================="
echo "Time taken by main_time: ${main_time_taken} ms"
echo "Time taken by AES: ${aes_time_taken} ms"

# Improvement calculation
improvement_aes=$(echo "scale=2; ($aes_time_taken - $main_time_taken) / $main_time_taken * 100" | bc)

echo "Improvement in timing: ${improvement_aes}%"
echo "========================================================="

# End of script

