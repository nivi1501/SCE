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

bool debug = false;
bool print = false;


int main() {
    string path = "ECG.dat";
    //string path = "data.csv";
    /* ---------------------------------------File Read ----------------------------------------------------- */
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
    int i = 0;

    auto encryptionStart = chrono::high_resolution_clock::now(); // Start time for encryption

while (i != (size_main / 64)) {
    int mid = 32;
    int strt = 0;

    // Precompute constants
    const double precomputedFactor = 1e4;

    // Pointer to the current 64-byte chunk
    int baseIndex = i * 64;

    // First stage: Permute first 32 and last 32 bytes
    while (mid != 64 && strt != 32) {
        double newVal = r * old * (1 - old);
        if (newVal < 0.5) {
            std::swap(weight[baseIndex + strt], weight[baseIndex + mid]);
            strt++;
            mid++;
        } else {
            strt++;
        }
        old = newVal;
    }

    // Second stage: Shuffle the remaining bytes
    int run = (64 - mid > 0) ? mid : 62;
    for (int it = run + 1; it < 63; ++it) {
        double newVal = r * old * (1 - old);
        int j = static_cast<int>(newVal * precomputedFactor) % (it - run);
        std::swap(weight[baseIndex + it], weight[baseIndex + run + j]);
        old = newVal;
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





    /* --------------------------------------- Substitution ------------------------------------------------- */
    int compressedSize = dataCompressed.size();
    string encryptedData = chaos(compressedSize, dataCompressed);

     auto encryptionEnd = chrono::high_resolution_clock::now();
     auto encryptionDuration = chrono::duration_cast<chrono::milliseconds>(encryptionEnd - encryptionStart).count();



    double compressionPercentage = (1 - static_cast<double>(compressedSize) / originalSize) * 100;

    cout << "Compression Percentage: " << compressionPercentage << "%" << endl;
    cout << "Time taken: " << encryptionDuration << " ms" << endl;


    if (print) {
        cout << "Encrypted Data: " << encryptedData << endl;
    }

    ofstream outfile("crypto_compressed_data.dat", ios::binary);
    if (outfile) {
        outfile.write(encryptedData.data(), encryptedData.size());
        outfile.close();
        cout << "Crypto-compressed data saved to crypto_compressed_image.dat" << endl;
    } else {
        cerr << "Error writing to file: crypto_compressed_image.dat" << endl;
    }


// Uncomment to store the data in the file for NIST testing
/*
       string filenameOut="sts-2_1_2/data/Output.txt";
       cout<< "Data stored in " << filenameOut<<endl;
	ofstream out1(filenameOut);
        
       for (int l=0; l<encryptedData.size(); l++)
       {
         //out1 << encryptedData.at(l)<<endl;
         out1 << bitset<8>(encryptedData.at(l)) <<endl;
       }   
       out1.close();
*/
    return 0;
}


