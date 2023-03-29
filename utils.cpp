#include "utils.h"

using namespace std;

int8_t converted(float in)
{
   int8_t out ;
   float temp = in;
   long temp2 = temp * pow(10,14);
   long mod = 128;
   //cout << "multiplied value "<<temp2 << endl;
   out = temp2 % mod;
   // cout << "8-bit value "<< +out << endl;
   return out;
}

arrWrap_int* mapConversion (arrWrap_ch* in, int row, int col)
{
    arrWrap_int* out = new arrWrap_int[row*col];
    for (int i=0; i< row ; i++)
    {
       for(int j=0; j<col ; j++ ){
          (out+i*col+j)->arr[0]= converted((in+i*col+j)->arr[0]);
          (out+i*col+j)->arr[1]= converted((in+i*col+j)->arr[1]);
       }
    } 
    return out;
}


arrWrap_int* Conversion (arrWrap_ch* in, int row, int col)
{
    arrWrap_int* out = new arrWrap_int[row*col];
    for (int i=0; i< row ; i++)
    {
       for(int j=0; j<col ; j++ ){
          int a= (in+i*col+j)->arr[0];
          int b= (in+i*col+j)->arr[1];
          (out+i*col+j)->arr[0]= (a) % 128;
          (out+i*col+j)->arr[1]= (b) % 128;
       }
    } 
    return out;
}



struct arrWrap split_c(string str)
{
    struct arrWrap xi ;
    string w = "";
    int i=0;
    for (auto x : str)
    {
        if (x == ',')
        {
            xi.arr[i]=stoi(w);
            w = "";
            i++;
        }
        else {
            w = w + x;
        }
    }
    xi.var=w;
    return xi;
}


arrWrap_int* xorArr1D (vector<int8_t> in1,arrWrap_int* in2,int row, int col)
{
   arrWrap_int* out = new arrWrap_int[row*col];
   for (int i=0; i< row ; i++)
    {
       for(int j=0; j<col ; j++ ){
          int8_t temp= ((in1[i*col+j])+((in2+i*col+j)->arr[0])%128);
          //int8_t temp = in1[i*col+j];
          (out+i*col+j)->arr[0]= temp^((in2+i*col+j)->arr[0]) ;
         // (out+i*col+j)->arr[0]= (in1[i*col+j])^((in2+i*col+j)->arr[0]);
       }
    } 
   return out;
}


arrWrap_int* xorArrInv1D (arrWrap_int* in1,arrWrap_int* in2,int row, int col)
{
   arrWrap_int* out = new arrWrap_int[row*col];
   for (int i=0; i< row ; i++)
    {
       for(int j=0; j<col ; j++ ){
          int8_t temp1 = (in1+i*col+j)->arr[0];
          int8_t temp2 = (in2+i*col+j)->arr[0];
          int8_t temp= temp1 ^ temp2;
          //int8_t temp = in1[i*col+j];
          (out+i*col+j)->arr[0]= (temp - ((in2+i*col+j)->arr[0]) % 128) ;
          //(out+i*col+j)->arr[0]= (in1+i*col+j)->arr[0] ^ ((in2+i*col+j)->arr[0]);
       }
    } 
   return out;
}


arrWrap_int* xorRounds(int rounds,arrWrap_int* chaosMap, vector<int8_t> weightCompressed, int row)
{
    arrWrap_int* xored = xorArr1D(weightCompressed,chaosMap,row,1);

    vector<int8_t> multiple;
    if(rounds>1)
    for (int r=1; r<rounds; r++)
    {
     for(int v=0; v < row ; v++)
        multiple.push_back((xored+v)->arr[0]);
     xored=xorArr1D(multiple,chaosMap,row,1);
    }
  return xored;
}


arrWrap_int* xorInvRounds(int rounds,arrWrap_int* chaosMap, arrWrap_int* weightCompressed, int row)
{
    arrWrap_int* xored = xorArrInv1D(weightCompressed,chaosMap,row,1);
    if(rounds>1)
    for (int r=1; r<rounds; r++)
    {
      xored=xorArrInv1D(chaosMap,xored,row,1);
    }
  return xored;
}




arrWrap_int* xorArr2D (vector<int8_t> in1,arrWrap_int* in2,int row, int col)
{
   arrWrap_int* out = new arrWrap_int[row*col];
   for (int i=0; i< row ; i++)
    {
       for(int j=0; j<col ; j++ ){
          int8_t temp = ((in1[i*col+j])+((in2+i*col+j)->arr[0]) % 128);
          (out+i*col+j)->arr[0]= (temp^((in2+i*col+j)->arr[1])) ;
        //   (out+i*col+j)->arr[0]= (out+i*col+j)->arr[0] ^ (in2+i*col+j)->arr[1];
         // (out+i*col+j)->arr[1]= ((in1[i*col+j]->arr[1])^((in2+i*col+j)->arr[1]);
       }
    }
    
   return out;
}

arrWrap_int* xorArrInv2D (arrWrap_int* in1,arrWrap_int* in2,int row, int col)
{
   arrWrap_int* out = new arrWrap_int[row*col];
   for (int i=0; i< row ; i++)
    {
       for(int j=0; j<col ; j++ ){
          int8_t temp1 = (in1+i*col+j)->arr[0];
          int8_t temp2 = (in2+i*col+j)->arr[0];
          int8_t temp= temp1 ^ temp2 ;
          //int8_t temp = in1[i*col+j];
          (out+i*col+j)->arr[0]= (temp - ((in2+i*col+j)->arr[0]) % 128) ;
       //   (out+i*col+j)->arr[0]= (out+i*col+j)->arr[0]^in2+i*col+j)->arr[1];
          //(out+i*col+j)->arr[0]= (in1+i*col+j)->arr[0] ^ ((in2+i*col+j)->arr[0]);
       }
    } 
   return out;
}



arrWrap_int* xorArrNew (vector<int8_t> in1,arrWrap_int* in2,int row, int col,int8_t prev)
{
   arrWrap_int* out = new arrWrap_int[row*col];
   for (int i=0; i< row ; i++)
    {
       for(int j=0; j<col ; j++ ){
          int8_t temp = ((in1[i*col+j])+((in2+i*col+j)->arr[0]) % 128);
          (out+i*col+j)->arr[0]= (temp^((in2+i*col+j)->arr[1]))^prev ;
        //   (out+i*col+j)->arr[0]= (out+i*col+j)->arr[0] ^ (in2+i*col+j)->arr[1];
         // (out+i*col+j)->arr[1]= ((in1[i*col+j]->arr[1])^((in2+i*col+j)->arr[1]);
       }
    }
    
   return out;
}

arrWrap_int* xorArrInvNew (arrWrap_int* in1,arrWrap_int* in2,int row, int col,int8_t prev)
{
   arrWrap_int* out = new arrWrap_int[row*col];
   for (int i=0; i< row ; i++)
    {
       for(int j=0; j<col ; j++ ){
          int8_t temp1 = (in1+i*col+j)->arr[0];
          int8_t temp2 = (in2+i*col+j)->arr[0];
          int8_t temp= temp1 ^ temp2^prev ;
          //int8_t temp = in1[i*col+j];
          (out+i*col+j)->arr[0]= (temp - ((in2+i*col+j)->arr[0]) % 128) ;
       //   (out+i*col+j)->arr[0]= (out+i*col+j)->arr[0]^in2+i*col+j)->arr[1];
          //(out+i*col+j)->arr[0]= (in1+i*col+j)->arr[0] ^ ((in2+i*col+j)->arr[0]);
       }
    } 
   return out;
}





arrWrap_int* xorArr3D (vector<int8_t> in1,arrWrap_int* in2,int row, int col)
{
   arrWrap_int* out = new arrWrap_int[row*col];
   for (int i=0; i< row ; i++)
    {
       for(int j=0; j<col ; j++ ){
          (out+i*col+j)->arr[0]= ((in1[i*col+j])^((in2+i*col+j)->arr[0])^((in2+i*col+j)->arr[1])) ;
         // (out+i*col+j)->arr[1]= ((in1[i*col+j]->arr[1])^((in2+i*col+j)->arr[1]);
       }
    } 
   return out;
}




float correlationCoefficientExt(vector<int8_t> X, vector<int8_t> Y)
{  
    float sum_X = 0, sum_Y = 0, sum_XY = 0;
    float squareSum_X = 0, squareSum_Y = 0;
    int n=X.size();
    for (int i = 0; i < X.size(); i++)
    {
        // sum of elements of array X.
        sum_X = sum_X + X.at(i);
        // sum of elements of array Y.
        sum_Y = sum_Y + Y.at(i);
        sum_XY = sum_XY + X.at(i) * Y.at(i);
        // sum of square of array elements.
        squareSum_X = squareSum_X + X.at(i) * X.at(i);
        squareSum_Y = squareSum_Y + Y.at(i) * Y.at(i);
     }
    // use formula for calculating correlation coefficient.
    float corr = (float)(n * sum_XY - sum_X * sum_Y) 
                  / sqrt((n * squareSum_X - sum_X * sum_X) 
                      * (n * squareSum_Y - sum_Y * sum_Y));
  return corr;
}


//Fuction to verify if the compression and decompression results are the same
void verifyResult(string path, string dataDecompressed)
{
    std::ifstream inStream(path, std::ios_base::in);
    std::stringstream decompressed;
    boost::iostreams::copy(inStream, decompressed);
    if (decompressed.str() == dataDecompressed) {
      cout << "The two strings are equal."<<endl;   } 
    else {
      cout << "ERROR!!!!!!  The two strings are not equal.";     }
}






