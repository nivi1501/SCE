#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <cstring>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/zstd.hpp>
#include <chrono>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <algorithm>

// Include the AES structures and methods from your provided AES code
#include "encrypt.h" // Ensure you have the AES code saved in this header
#include "utils.h"

using namespace std;

bool debug = false;
bool print = false;


string customAESEncrypt(string& data, unsigned char* key) {
    // Expand key
    unsigned char expandedKey[176];
    KeyExpansion(key, expandedKey);

    // Pad data to 16-byte blocks
    size_t originalSize = data.size();
    size_t paddedSize = ((originalSize + 15) / 16) * 16;
    
    // Using std::list instead of vector
    std::list<unsigned char> paddedData(paddedSize, 0);
    auto it = paddedData.begin();
    
    // Copy data to the list 
    for (size_t i = 0; i < originalSize; ++i, ++it) {
        *it = static_cast<unsigned char>(data[i]);
    }

    // Prepare encrypted data as a list
    std::list<unsigned char> encryptedData(paddedSize, 0);

    // Encrypt each 16-byte block
    auto paddedIt = paddedData.begin();
    auto encryptedIt = encryptedData.begin();

    while (paddedIt != paddedData.end()) {
        // Copy 16 bytes to an array for processing
        unsigned char block[16] = {0};
        unsigned char encryptedBlock[16] = {0};

        for (int i = 0; i < 16 && paddedIt != paddedData.end(); ++i, ++paddedIt) {
            block[i] = *paddedIt;
        }

        // Encrypt the block
        AESEncrypt(block, expandedKey, encryptedBlock);

        // Copy encrypted block back to the encryptedData list
        for (int i = 0; i < 16 && encryptedIt != encryptedData.end(); ++i, ++encryptedIt) {
            *encryptedIt = encryptedBlock[i];
        }
    }

    // Convert list back to a string
    std::string encryptedString;
    encryptedString.reserve(encryptedData.size());
    for (auto c : encryptedData) {
        encryptedString.push_back(static_cast<char>(c));
    }

    return encryptedString;
}



// Compression function
string compressData(const string& data) {
    stringstream compressed;
    stringstream dataStream(data);
    boost::iostreams::filtering_streambuf<boost::iostreams::input> out;
    boost::iostreams::zstd_params params;
    params.level = 3;
    out.push(boost::iostreams::zstd_compressor(params));
    out.push(dataStream);
    boost::iostreams::copy(out, compressed);
    return compressed.str();
}


int main() {
    string path = "ECG.dat";

    /* --------------------------------------- File Read ----------------------------------------------------- */
    vector<int8_t> weight;
    ifstream myfile(path, ios_base::binary);
    if (!myfile) {
        cerr << "Error opening file: " << path << endl;
        return -1;
    }
    weight.assign(istreambuf_iterator<char>(myfile), istreambuf_iterator<char>());
    myfile.close();

    // Start the timer
    auto encryptionStart = chrono::high_resolution_clock::now();

    /* Prepare Data for Encryption */
    stringstream outData2;
    for (auto& w : weight) {
        outData2 << ((w));
    }
    string originalData = outData2.str();

    /* --------------------------------------- Custom AES Encryption ------------------------------------------------ */
    unsigned char aesKey[16] = {'t', 'h', 'i', 's', '_', 'i', 's', '_', 'a', 'e', 's', '_', 'k', 'e', 'y', '!'};

    string encryptedData = customAESEncrypt(originalData, aesKey);

    /* --------------------------------------- Compression -------------------------------------------------- */
    string compressedData = compressData(encryptedData);

    int compressedSize = compressedData.size();
    double compressionPercentage = (1 - static_cast<double>(compressedSize) / originalData.size()) * 100;

    auto encryptionEnd = chrono::high_resolution_clock::now();
    auto encryptionDuration = chrono::duration_cast<chrono::milliseconds>(encryptionEnd - encryptionStart).count();

    cout << "Compression Percentage: " << compressionPercentage << "%" << endl;
    cout << "Time taken: " << encryptionDuration << " ms" << endl;

    return 0;
}

