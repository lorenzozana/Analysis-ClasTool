#ifndef __TArray_7__
#define __TArray_7__

class TArray_7
{
 protected:
 
    int		fn_bin_x ,
    		fn_bin_y ,
    		fn_bin_z ,
    		fn_bin_t ;
    		
    int 	fn_bin_total;		
    		    		
    float* 	fArray ;
    
 public:
 
 		TArray_7( int n_x, int n_y, int n_z, int n_t );		
   		TArray_7( const TArray_7& Array ) ;		
 		~TArray_7();
 
   void	       operator=( TArray_7& Array );

   TArray_7    operator-();
	
   TArray_7    operator+( TArray_7& Array );
   TArray_7    operator-( TArray_7& Array );
   TArray_7    operator*( TArray_7& Array );
   TArray_7    operator/( TArray_7& Array );
 		
   float&       Value( int ix, int iy, int iz, int it );
   
};

#endif


