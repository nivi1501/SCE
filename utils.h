#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
#include <sstream>
#include <string>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <bitset>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/zlib.hpp>
#include <boost/iostreams/filter/bzip2.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/asio.hpp>
#include <boost/iostreams/filter/lzma.hpp>
#include <boost/iostreams/filter/zstd.hpp>
#include <experimental/filesystem>
#include <boost/iostreams/detail/config/dyn_link.hpp>
#include "lz4.h"
#include <typeinfo>
#include <boost/numeric/conversion/cast.hpp>
#include <boost/lexical_cast.hpp>
using boost::lexical_cast;
using boost::numeric_cast;


using namespace std;

struct arrWrap_ch {
    float arr[2];
};

struct arrWrap_ch_3D {
    float arr[3];
};


struct arrWrap_int {
    int8_t arr[2];
};

struct arrWrap {
    int arr[2];
    std::string var;
};

//using namespace std;

arrWrap split_c(std::string str);
arrWrap_int* mapConversion (arrWrap_ch* in, int row, int col);
int8_t converted(float in);
arrWrap_int* xorArr1D (vector<int8_t> in1,arrWrap_int* in2,int row, int col);
arrWrap_int* xorArr2D (vector<int8_t> in1,arrWrap_int* in2,int row, int col);
arrWrap_int* xorArr3D (vector<int8_t> in1,arrWrap_int* in2,int row, int col);
float correlationCoefficient(float X[], float Y[], int row, int col);
float correlationCoefficientInt(int8_t X[], int8_t Y[], int row, int col);
double correlationCoefficient1D(string X, string Y);
arrWrap_int* Conversion (arrWrap_ch* in, int row, int col);
arrWrap_int* xorArrInv1D (arrWrap_int* in1,arrWrap_int* in2,int row, int col);
void verifyResult(string path, string dataDecompressed);
arrWrap_int* xorRounds(int rounds,arrWrap_int* chaosMap, vector<int8_t> weightCompressed, int row);
arrWrap_int* xorInvRounds(int rounds,arrWrap_int* chaosMap, arrWrap_int* weightCompressed, int row);
arrWrap_int* xorArrInv2D (arrWrap_int* in1,arrWrap_int* in2,int row, int col);
arrWrap_int* xorArr2D (vector<int8_t> in1,arrWrap_int* in2,int row, int col);
arrWrap_int* xorArrInvNew (arrWrap_int* in1,arrWrap_int* in2,int row, int col,int8_t prev);
arrWrap_int* xorArrNew (arrWrap_int* in1,arrWrap_int* in2,int row, int col,int8_t prev);
 string dataRead(string path,string file);
#endif
