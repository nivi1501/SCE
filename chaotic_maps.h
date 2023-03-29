#include "utils.h"

#ifndef CHAOTIC_MAPS_H
#define CHAOTIC_MAPS_H

arrWrap_ch* chirikov(int row, int col);
arrWrap_ch* arnoldCatMap(int row, int col);
arrWrap_ch* henonMap(int row, int col, int dim);
arrWrap_ch* logisticMap(int row, int col);
arrWrap_ch* tentMap(int row, int col);
arrWrap_ch_3D* lorentzMap(int row, int col);
arrWrap_ch* lorentzMap2D(int row, int col);
float *temp_map(int row, int col);
string chaos(int row, string dataCompressed);
string dechaos(int row, string dataCompressed);
//arrWrap_ch* chirikov_fast(int row, int col);
//float sin_fast(float x);
#endif

