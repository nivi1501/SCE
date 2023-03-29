
#include "chaotic_maps.h"

#include <chrono>

using namespace std;

using boost::lexical_cast;

using boost::numeric_cast;

bool debug = 0;

bool print = 0;

bool testData = 1;


int main()
{
 
 for(int ki=0; ki <5 ; ki++)
 {
   
   // Update this variable to the location of the data you wish to compress
   string path;   
   
   
   /* ---------------------------------------File read -----------------------------------------------------*/
   vector<int8_t> weight;
   std::ifstream myfile (path, std::ios_base::binary); //
   
   // Read the data and store in a vector
   
   
   

   /* ---------------------------------------Dummy Data Generation for POC -----------------------------------------------------*/
   // vector<int8_t> weight;
   
   // Data generation
   // Read your data here ----
   int size_main = weight.size();
   
   if(testData == 1)
   {
     int size_main = 256 ;
     for(int i = 0; i<size_main ; i++)
     {
       weight.push_back(i);
     }
   }
   
    // Constant variable declaration
    double r = 3.94;
    double old = 0.2;
    int i = 0;
    int mid = 0;
    
    //--------------------------------------- Keep on permutating the data in the chunks of 64 bytes ------------------------------------------//
    
 // Timing information
    while((i) != (size_main)/64)
    { 

       int mid = 32;
       int strt = 0;
    

       while(mid!=64 and strt != 32)
       {
       
                   
          //Generation of the logistic map
          double newVal = r*old*(1-old);
          
          // Compare the value of the logistic map with the secret threshold
          if(newVal < 0.012 )
          { 
          
             	    
	    // Swap the values
            char swap = weight.at(strt+i*64);
            weight.at(strt+i*64) = weight.at(mid+i*64);
            weight.at(mid+i*64) = swap;
            strt = strt + 1;
            mid = mid + 1;
          }
          
          else
          {
            strt = strt + 1;
          }
            
          // Update the logistic map last value
          old=newVal;
      }
	
      int n = 0;
      int run = 0;

	// If variables are left in the second array for permutation
      if(64-mid > 0)
      {
	        run = mid;
		n = 63;
      }
      
	// If all the content is already shuffled
      else
      {
	        run = 62;
		n = 63;
      }
	
	
	
	
	// 'strt' till 32 is already depleted
	// shuffle the array between the location pointed by 'mid' and 63
        for(int it = run+1 ; it != n ; it++)
        { 
               // Swapping based on the value of the logistic map
        	double newVal = r*old*(1-old);
        	int diff = 63 - it ;
        	int j = int(newVal*pow(10,4)) % (it-1 );
        	//save.push_back(j);
        	
        	        	
        	// Swap the values   
	        char swap = weight.at(it+i*64);
		weight.at(it+i*64) = weight.at(j+i*64);
        	weight.at(j+i*64) = swap;
        	
        	// Update the old value of the Logistic map
        	old = newVal;
         }
         
      // Increment 'i', to point to the next 64 bytes chunk
      i = i+1;
      
    }   
     
     
    // We need to send the stringstream datatype for compression. We had a vector of int8_t datatype
    stringstream outData2;
    
    int col =  weight.size();
    
    for(int j=0; j< col ; j++)
    {
        outData2 << ((weight[j]));
    }
    
    
    //----------------------- Compression starts from here ----------------------------------//
    stringstream inStream;
    boost::iostreams::filtering_streambuf<boost::iostreams::input> out;
    
    // Control the level of compression using the 'level' parameter
    boost::iostreams::zstd_params params;
    //params.level = 5;
    out.push(boost::iostreams::zstd_compressor(params));
    
    out.push(outData2);

    std::stringstream compressed;

    boost::iostreams::copy(out, compressed);
 
    string dataCompressed = compressed.str();

    int row_new = (dataCompressed).size();
    

    
    //----------------------- Encryption starts from here ----------------------------------//
    string arr1 = chaos(row_new, dataCompressed);
    
       
       
    // arr1 is the final crypto-compressed data
    
    if(print == 1)
    {
        cout << "****************** The final crypto-compressed values are ****************" << endl; 
        cout << arr1 << endl;
    }
  }  
 return 0;

}

