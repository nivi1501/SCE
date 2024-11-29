#include "chaotic_maps.h"
#include <chrono>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/zstd.hpp>

using namespace std;

// Decompression function
string decompressData(const string& compressed) {
    stringstream decompressed;
    stringstream compressedStream(compressed);
    boost::iostreams::filtering_streambuf<boost::iostreams::input> in;
    in.push(boost::iostreams::zstd_decompressor());
    in.push(compressedStream);
    boost::iostreams::copy(in, decompressed);
    return decompressed.str();
}

// Function to perform de-permutation
void decryptPermutation(vector<int8_t>& data, const vector<int>& run_values, const vector<double>& logistic_seq) {
    int size_main = data.size();
    int i = (size_main / 64) - 1; // Start from the last chunk

    while (i >= 0) {
        int run = run_values.at(i);
        int n = 63;

        // Reverse second stage: Unshuffle based on logistic map
        for (int it = n - 1; it > run; --it) {
            double newVal = logistic_seq[i * 64 + it];
            int j = int(newVal * pow(10, 4)) % (it - run);
            swap(data.at(it + i * 64), data.at(run + j + i * 64));
        }

        int mid = 32;
        int strt = 0;

        // Reverse first stage: Undo swaps
        while (mid != 64 && strt != 32) {
            double newVal = logistic_seq[i * 64 + strt];
            if (newVal < 0.5) {
                swap(data.at(strt + i * 64), data.at(mid + i * 64));
                strt++;
                mid++;
            } else {
                strt++;
            }
        }

        i--; // Move to the previous chunk
    }
}

// Main function
int main() {
    string path = "data.csv";

    /* --------------------------------------- File Read ----------------------------------------------------- */
    vector<int8_t> weight;
    ifstream myfile(path, ios_base::binary);
    if (!myfile) {
        cerr << "Error opening file: " << path << endl;
        return -1;
    }
    weight.assign(istreambuf_iterator<char>(myfile), istreambuf_iterator<char>());
    myfile.close();

    int size_main = weight.size();

    /* --------------------------------------- Permutation Logic -------------------------------------------- */
    double r = 3.94;
    double old = 0.2;
    vector<double> logistic_seq(size_main); // Store logistic sequence for reuse
    vector<int> run_values;

    int i = 0;
    while (i != (size_main) / 64) {
        int mid = 32;
        int strt = 0;

        // Generate logistic map values for this chunk
        for (int j = 0; j < 64; ++j) {
            logistic_seq[i * 64 + j] = r * old * (1 - old);
            old = logistic_seq[i * 64 + j];
        }

        // First stage: Permute first 32 and last 32 bytes
        while (mid != 64 && strt != 32) {
            if (logistic_seq[i * 64 + strt] < 0.5) {
                swap(weight.at(strt + i * 64), weight.at(mid + i * 64));
                strt++;
                mid++;
            } else {
                strt++;
            }
        }

        // Second stage: Shuffle the remaining bytes
        int run = (64 - mid > 0) ? mid : 62;
        run_values.push_back(run);
        for (int it = run + 1; it < 63; ++it) {
            int j = int(logistic_seq[i * 64 + it] * pow(10, 4)) % (it - run);
            swap(weight.at(it + i * 64), weight.at(run + j + i * 64));
        }

        i++;
    }

    // Prepare data for compression
    stringstream outData2;
    for (auto& w : weight) {
        outData2 << ((w));
    }

    int originalSize = outData2.str().size();

    /* --------------------------------------- Compression -------------------------------------------------- */
    stringstream compressed;
    {
        boost::iostreams::filtering_streambuf<boost::iostreams::input> out;
        boost::iostreams::zstd_params params;
        params.level = 3;
        out.push(boost::iostreams::zstd_compressor(params));
        out.push(outData2);
        boost::iostreams::copy(out, compressed);
    }

    string dataCompressed = compressed.str();
    int compressedSize = dataCompressed.size();
    double compressionPercentage = (1 - static_cast<double>(compressedSize) / originalSize) * 100;

    cout << "Compression Percentage: " << compressionPercentage << "%" << endl;

    /* --------------------------------------- Substitution ------------------------------------------------- */
    string encryptedData = chaos(compressedSize, dataCompressed);

    // Decrypt substitution
    string decryptedData = dechaos(compressedSize, encryptedData);
    if (dataCompressed == decryptedData) {
        cout << "Decryption successful! Decrypted data matches the compressed data." << endl;
    } else {
        cout << "Decryption failed! Decrypted data does not match the compressed data." << endl;
    }

    // Decompress the decrypted data
    string decompressedData = decompressData(decryptedData);
    if (outData2.str() == decompressedData) {
        cout << "Decompression successful! Decompressed data matches the original data." << endl;
    } else {
        cout << "Decompression failed! Decompressed data does not match the original data." << endl;
    }

    /* --------------------------------------- De-permutation Verification ---------------------------------- */
    decryptPermutation(weight, run_values, logistic_seq);
    ifstream file(path, ios_base::binary); // Create ifstream object with proper scope
    if (file) { // Check if the file was successfully opened
    vector<int8_t> original_data((istreambuf_iterator<char>(file)),
                                 istreambuf_iterator<char>());
    if (weight == original_data) {
        cout << "De-permutation successful! Data matches the original file." << endl;
    } else {
        cout << "De-permutation failed! Data does not match the original file." << endl;
    }
    } else {
        cerr << "Error opening file for verification: " << path << endl;
    }
    return 0;
}

