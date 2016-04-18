#ifndef __TArray_7__
#define __TArray_7__

#include "TObject.h"

class TArray_7: public TObject 
{
 protected:
 
    int		fn_bin_x ,
    		fn_bin_y ,
    		fn_bin_z ,
    		fn_bin_t ,
                fn_bin_i ,
    		fn_bin_j ,
    		fn_bin_k ;
    
    		
    int 	fn_bin_total;		
    		    		
    float* 	fArray ;
    
 public:
 
 		TArray_7( int n_x, int n_y, int n_z, int n_t, int n_i , int n_j , int n_k );		
   		TArray_7( const TArray_7& Array ) ;		
 		~TArray_7();
 
   void	       operator=( TArray_7& Array );

   TArray_7    operator-();
	
   TArray_7    operator+( TArray_7& Array );
   TArray_7    operator-( TArray_7& Array );
   TArray_7    operator*( TArray_7& Array );
   TArray_7    operator/( TArray_7& Array );
 		
   float&       Value( int ix, int iy, int iz, int it , int ii , int ij , int ik );

  ClassDef(TArray_7,1) // A Class for Array for Acceptance in eg2.
    ;
   
};

#endif


