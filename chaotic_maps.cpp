#include "chaotic_maps.h"
  
  
arrWrap_ch* chirikov(int row, int col)
{
//cout << "row " << row << " colc "<<col <<endl;
    int size =0;
    int tr=10;
    int val = row*col;
    if(val > 100)
       size=val+1;
    else
       size=102;
          
    arrWrap_ch* ary = new arrWrap_ch[size];
    int k = 10;
    (ary)->arr[0] = 7;
    (ary)->arr[1] = 8;
    
    float temp1,temp2;
    for(int i=0; i<tr; i++){
     for(int j=0; j<tr; j++){
     float x = 2*3.14159*((ary+i*tr+j)->arr[1]);
     float pi = 2*3.14159;
          (ary+i*tr+j+1)->arr[0] = fmod((ary+i*tr+j)->arr[0] - k*sin(x), pi) ;
          (ary+i*tr+j+1)->arr[1] = fmod((ary+i*tr+j)->arr[1] + (ary+i*tr+j+1)->arr[0], pi);
          temp1=(ary+i*tr+j+1)->arr[0];
          temp2=(ary+i*tr+j+1)->arr[1];
       }
    }
    
    ary->arr[0]=temp1;
    ary->arr[1]=temp2;
    
    //This parameter acts as a key and decides degree of deviation in the image
      
    for(int i=0; i<row; i++){
     for(int j=0; j<col; j++){
     float x = 2*3.14159*((ary+i*col+j)->arr[1]);
     float pi = 2*3.14159;
          (ary+i*col+j+1)->arr[0] = fmod((ary+i*col+j)->arr[0] - k*sin(x), pi) ;
          (ary+i*col+j+1)->arr[1] = fmod((ary+i*col+j)->arr[1] + (ary+i*col+j+1)->arr[0], pi);
          //cout << " i " << i << " j "<< j  << " " <<i*col+j+1 << endl;
       }
    }
    //cout << " out " << endl;  
    return ary;
}

/*float sin_fast(float x) {
    constexpr float PI = 3.14159265358f;
    constexpr float B = 4.0f / PI;
    constexpr float C = -4.0f / (PI * PI);
    constexpr float P = 0.225f;

    float y = B * x + C * x * (x < 0 ? -x : x);
    return P * (y * (y < 0 ? -y : y) - y) + y;
}


arrWrap_ch* chirikov_fast(int row, int col)
{
//cout << "row " << row << " colc "<<col <<endl;
    int size =0;
    int tr=10;
    if(col*row > 100)
       size=col*row;
    else
       size=100;
          
    arrWrap_ch* ary = new arrWrap_ch[size];
    int k = 10;
    (ary)->arr[0] = 7;
    (ary)->arr[1] = 8;
    
    float temp1,temp2;
    for(int i=0; i<tr; i++){
     for(int j=0; j<tr; j++){
     float x = 2*3.14159*((ary+i*tr+j)->arr[1]);
     float pi = 2*3.14159;
          (ary+i*tr+j+1)->arr[0] = fmod((ary+i*tr+j)->arr[0] - k*sin_fast(x), pi) ;
          (ary+i*tr+j+1)->arr[1] = fmod((ary+i*tr+j)->arr[1] + (ary+i*tr+j+1)->arr[0], pi);
          temp1=(ary+i*tr+j+1)->arr[0];
          temp2=(ary+i*tr+j+1)->arr[1];
       }
    }
    
    ary->arr[0]=temp1;
    ary->arr[1]=temp2;
    
    //This parameter acts as a key and decides degree of deviation in the image
      
    for(int i=0; i<row; i++){
     for(int j=0; j<col; j++){
     float x = 2*3.14159*((ary+i*col+j)->arr[1]);
     float pi = 2*3.14159;
          (ary+i*col+j+1)->arr[0] = fmod((ary+i*col+j)->arr[0] - k*sin_fast(x), pi) ;
          (ary+i*col+j+1)->arr[1] = fmod((ary+i*col+j)->arr[1] + (ary+i*col+j+1)->arr[0], pi);
          //cout << " i " << i << " j "<< j  << " " <<i*col+j+1 << endl;
       }
    }
    //cout << " out " << endl;  
    return ary;
}*/







arrWrap_ch* arnoldCatMap(int row, int col)
{
    //The number of iterations needed to restore the image can be shown never to exceed 3N.
    arrWrap_ch* ary = new arrWrap_ch[col*row];
    //This parameter acts as a key and decides degree of deviation in the image
   
    
    for(int i=0; i<row; i++){ //y 
     for(int j=0; j<col; j++){  //x
          //if(i==0 || j==0){
          //(ary+i*col+j)->arr[0] = i; //x
          //(ary+i*col+j)->arr[1] = j; //y          
          //}
          //else{
          (ary+i*col+j)->arr[0] = (2*j + i +1)  ; //x
          (ary+i*col+j)->arr[1] = (i + j +1) ; //y
          //}
       }
    }  
    return ary;
}
	/*for row = 1 : rows % y
		for col = 1 : columns % x
			c = mod((2 * col) + row, N) + 1; % x coordinate
			r = mod(col + row, N) + 1; % y coordinate
            c 
			% Move the pixel.  Note indexes are (row, column) = (y, x) NOT (x, y)!
			currentScrambledImage(row, col, :) = oldScrambledImage(r, c, :);
		end
	end*/
	
arrWrap_ch* henonMap(int row, int col,int dim)
{
   float b=0.3;
   float a=1.4;
//src:http://www.m-hikari.com/ijma/ijma-2012/ijma-49-52-2012/alshameriIJMA49-52-2012.pdf
       int size =0;
    int val = row*col;
    if(val > 100)
       size=val;
    else
       size=102;
      
   arrWrap_ch* ary = new arrWrap_ch[size];
   (ary+0)->arr[0]=0.1;
   (ary+0)->arr[1]=0.3;
    
   float temp1,temp2;
   int tr=10;
   if(dim==2)
    { 
    for(int i=0; i<tr; i++){
     for(int j=0; j<tr; j++){
          (ary+i*tr+j+1)->arr[0] = 1-a*pow((ary+i*tr+j)->arr[0],2)+(ary+i*tr+j)->arr[1];
          (ary+i*tr+j+1)->arr[1] = b*(ary+i*tr+j)->arr[0];
          temp1 =  (ary+i*tr+j+1)->arr[0];
          temp2 =  (ary+i*tr+j+1)->arr[1];
       //  cout << "temp " << temp << endl;
          //(ary+i*col+j)->arr[1] = b*i;
       }
    }  
    ary->arr[0] = temp1 ;  
    ary->arr[1] = temp2 ;  
    //This parameter acts as a key and decides degree of deviation in the image
    for(int i=0; i<row; i++){
     for(int j=0; j<col; j++){
          (ary+i*col+j+1)->arr[0] = 1-a*pow((ary+i*col+j)->arr[0],2)+(ary+i*col+j)->arr[1];
          (ary+i*col+j+1)->arr[1] = b*(ary+i*col+j)->arr[0];
       }
      }
   }
   
   
   else
    {
      for(int i=0; i<tr*tr; i++)
      {
          (ary+i+1)->arr[0] = 1-a*pow((ary+i)->arr[0],2)+(ary+i)->arr[1];
          (ary+i+1)->arr[1] = b*(ary+i)->arr[0];
         temp1 =  (ary+i+1)->arr[0];
          temp2 =  (ary+i+1)->arr[1];
      }
       ary->arr[0] = temp1 ;  
       ary->arr[1] = temp2 ;  
       
       for(int i=0; i<tr*tr; i++)
       {
          (ary+i+1)->arr[0] = 1-a*pow((ary+i)->arr[0],2)+(ary+i)->arr[1];
          (ary+i+1)->arr[1] = b*(ary+i)->arr[0];
       }
    }
    return ary;
}




arrWrap_ch_3D* lorentzMap(int row, int col)
{
   float sigma = 10;
   float R = 28;
   float b = -2.67;
   arrWrap_ch_3D* arr = new arrWrap_ch_3D[col*row];
   (arr)->arr[0] = 5;
   (arr)->arr[1] = 5;
   (arr)->arr[2] = 5;
   
   for(int i=0; i<row; i++){
    for(int j=0; j<col; j++){
        float x = (arr+i*col+j)->arr[0] ;
        float y = (arr+i*col+j)->arr[1] ; 
        float z = (arr+i*col+j)->arr[2] ; 
        (arr+i*col+j+1)->arr[0] = sigma * ( y - x ) ;
        (arr+i*col+j+1)->arr[1] = R*x - x*z - y ;
        (arr+i*col+j+1)->arr[2] = b*z + x*y  ;
      }
    }
   return arr; 
}


arrWrap_ch* lorentzMap2D(int row, int col)
{
   float sigma = 10;
   float R = 28;
   float b = 2.67;
   arrWrap_ch* arry = new arrWrap_ch[col*row+1];
   (arry)->arr[0] = 5;
   (arry)->arr[1] = 6;
   float temp = 5;
   float tempx,tempy;
   int tr = 10;
   /*for(int i=0; i<tr; i++){
    for(int j=0; j<tr; j++){
        //cout << i*col+j << endl;
        double x = ((arry+i*col+j)->arr[0]) ;
        double y = ((arry+i*col+j)->arr[1]) ; 
        double z = (temp) ; 
        //cout << x << " " << y << " " << z << endl;
        (arry+i*col+j+1)->arr[0] = fmod(sigma * ( y - x ),10^34) ;
        (arry+i*col+j+1)->arr[1] = fmod((R*x) - (x*z) - y, 10^34 );
        temp =  fmod((x*y) - (b*z), 10^34)  ;
        tempx=(arry+i*col+j+1)->arr[0];
        tempy=(arry+i*col+j+1)->arr[1];
      }

    }*/
   
   //(arry+0)->arr[0] = tempx ;
   //(arry+0)->arr[1] =  tempy;
   //cout << tempx << endl;
   
   for(int i=0; i<row; i++){
    for(int j=0; j<col; j++){
        //cout << i*col+j << endl;
        float x = (arry+i*col+j)->arr[0] ;
        float y = (arry+i*col+j)->arr[1] ; 
        float z = temp ; 
        (arry+i*col+j+1)->arr[0] = (sigma * ( y - x )) ;
        (arry+i*col+j+1)->arr[1] = ((R*x) - (x*z) - y );
        temp =  ((x*y) - (b*z))  ;
        //cout << x << endl;
      }
    }
   return arry; 
}


float mfmod(float x,float y) { float a; return ((a=x/y)-(int)a)*y; }
string chaos(int row, string dataCompressed)
{
   int col = 1;
   float sigma = 10;
   float R = 28;
   float b = -2.67;
   arrWrap_ch* arry = new arrWrap_ch[row+1];
   string out;
   arrWrap_ch* ary = new arrWrap_ch[row+1];

   (arry)->arr[0] = 0;
   (arry)->arr[1] = 1;
   float temp = 0;
   int tr = 10;
   float tempx,tempy;
   
   //Generation of a 3D Lorenz map
   for(int i=0; i<tr; i++)
   {
   
    for(int j=0; j<tr; j++)
    {
    
        //cout << i*col+j << endl;
        double x = ((arry+i*col+j)->arr[0]) ;
        double y = ((arry+i*col+j)->arr[1]) ; 
        double z = (temp) ; 
        //cout << x << " " << y << " " << z << endl;
        (arry+i*col+j+1)->arr[0] = mfmod( (sigma * ( y - x )),10^34 ) ;
        (arry+i*col+j+1)->arr[1] = mfmod( (R*x) - (x*z) - y  , 10^34);
        temp =  fmod((x*y) - (b*z), 10^34)  ;
        tempx=(arry+i*col+j+1)->arr[0];
        tempy=(arry+i*col+j+1)->arr[1];
      }
      
    }
   
   //Store the last map values, to skip the transient effects
   (arry+0)->arr[0] = tempx ;
   (arry+0)->arr[1] = tempy;

   // Start the actual iterations
   int8_t ols = 0;
   for(int i=0; i<row; i++)
   {
        float x = (arry+i)->arr[0] ;
        float y = (arry+i)->arr[1] ; 
        float z = temp ; 
        (arry+i+1)->arr[0] = mfmod( (sigma * ( y - x )),10^34 ) ;
        (arry+i+1)->arr[1] = mfmod( ((R*x) - (x*z) - y ),10^34 );
        temp = fmod( ((x*y) - (b*z)),10^34 ) ;
     
        //Convert the generated values to int and perform XOR
        long temp1 = (arry+i)->arr[0] * pow(10,14);
        int mod = 128;   
        int8_t out1 = temp1 % mod;
        
        // Generation of 2D Henon map   
        float a=1.4;
        (ary)->arr[0]=0.1;
        (ary)->arr[1]=0.3;   
        float bb=0.3;
        (ary+i+1)->arr[0] = 1-a*pow((ary+i)->arr[0],2)+(ary+i)->arr[1];
        (ary+i+1)->arr[1] = bb*(ary+i)->arr[0];
        //Convert the generated values to int and perform XOR 
        long temp2 = (ary+i)->arr[0] * pow(10,14);
        int8_t out2 = temp2 % mod;
        //cout << +out1 << endl;
        // Actual encryption starts from here
        int8_t t= int8_t(dataCompressed[i]) ^ out1;
        
        t = t ^ out2;
        t = t + ols;
        ols = t;
        out += (t);
        
    }
   return out; 
}


string dechaos(int row, string dataCompressed)
{
   cout << "***************************************" << endl;
   int col = 1;
   float sigma = 10;
   //actual sig
   //actual R was 28
   float R = 28;
   float b = 2.67;
   arrWrap_ch* arry = new arrWrap_ch[row+1];
   // arrWrap_ch* out = new arrWrap_ch[col*row+1];
    string out;
   arrWrap_ch* ary = new arrWrap_ch[row+1];

   (arry)->arr[0] = 5;
   (arry)->arr[1] = 6;
   float temp = 5;
   int tr = 10;
   float tempx,tempy;
   
   //Generation of a 3D Lorenz map
   for(int i=0; i<tr; i++){
    for(int j=0; j<tr; j++){
        //cout << i*col+j << endl;
        double x = ((arry+i*col+j)->arr[0]) ;
        double y = ((arry+i*col+j)->arr[1]) ; 
        double z = (temp) ; 
        //cout << x << " " << y << " " << z << endl;
        (arry+i*col+j+1)->arr[0] = (sigma * ( y - x )) ;
        (arry+i*col+j+1)->arr[1] = ((R*x) - (x*z) - y );
        temp =  ((x*y) - (b*z))  ;
        tempx=(arry+i*col+j+1)->arr[0];
        tempy=(arry+i*col+j+1)->arr[1];
      }
    }
   
   //Store the last map values, to skip the transient effects
   (arry+0)->arr[0] = tempx ;
   (arry+0)->arr[1] =  tempy;

   // Start the actual iterations
   int8_t ols = 0;
   for(int i=0; i<row; i++){
        float x = (arry+i)->arr[0] ;
        float y = (arry+i)->arr[1] ; 
        float z = temp ; 
        (arry+i+1)->arr[0] = (sigma * ( y - x )) ;
        (arry+i+1)->arr[1] = ((R*x) - (x*z) - y );
        temp =  ((x*y) - (b*z))  ;
     
        //Convert the generated values to int and perform XOR
        long temp1 = (arry+i)->arr[0] * pow(10,14);
        int mod = 128;   
        int8_t out1 = temp1 % mod;
        
        
        // Generation of 2D Henon map   
        float a=1.4;
        (ary)->arr[0]=0.1;
        (ary)->arr[1]=0.3;   
        float bb=0.3;
        (ary+i+1)->arr[0] = 1-a*pow((ary+i)->arr[0],2)+(ary+i)->arr[1];
        (ary+i+1)->arr[1] = bb*(ary+i)->arr[0];
        //Convert the generated values to int and perform XOR 
        long temp2 = (ary+i)->arr[0] * pow(10,14);
        int8_t out2 = temp2 % mod;
        
        // Actual encryption
        int8_t t = int8_t(dataCompressed[i]) - ols;
        t= t ^ out1;
        t = t ^ out2;
        
        ols = dataCompressed[i] ;
        out += (t);
    }
   return out; 
}























