
#include <iostream.h> 
#include <stdio.h>
#include <math.h>
#include "TArray_7.h"

TArray_7::TArray_7( int n_x, int n_y, int n_z, int n_t , int n_i , int n_j , int n_k )
{
 fn_bin_x = n_x;
 fn_bin_y = n_y;
 fn_bin_z = n_z;
 fn_bin_t = n_t;
 fn_bin_i = n_i;
 fn_bin_j = n_j;
 fn_bin_k = n_k;
 
 
 fn_bin_total = fn_bin_x * fn_bin_y * fn_bin_z * fn_bin_t * fn_bin_i * fn_bin_j * fn_bin_k;
 
 fArray = new float[fn_bin_total+1] ;
}


TArray_7::TArray_7( const TArray_7& Array )
{
 this->fn_bin_x = Array.fn_bin_x;
 this->fn_bin_y = Array.fn_bin_y;
 this->fn_bin_z = Array.fn_bin_z;
 this->fn_bin_t = Array.fn_bin_t;
 this->fn_bin_i = Array.fn_bin_i;
 this->fn_bin_j = Array.fn_bin_j;
 this->fn_bin_k = Array.fn_bin_k;
 
 this->fn_bin_total = Array.fn_bin_total ;
 
 this->fArray = new float[fn_bin_total+1] ; 
 
 for( int iBin = 0; iBin <= fn_bin_total; iBin++ )
  (this->fArray)[iBin] = (Array.fArray)[iBin] ;
}


TArray_7::~TArray_7()
{
 delete[] fArray;
}


void TArray_7::operator=( TArray_7& Array )
{
 if (
     ( this->fn_bin_x != Array.fn_bin_x ) ||
     ( this->fn_bin_y != Array.fn_bin_y ) ||
     ( this->fn_bin_z != Array.fn_bin_z ) ||
     ( this->fn_bin_t != Array.fn_bin_t ) ||
     ( this->fn_bin_i != Array.fn_bin_i ) ||
     ( this->fn_bin_j != Array.fn_bin_j ) ||
     ( this->fn_bin_k != Array.fn_bin_k )
    )
 {
  printf("Different type of Arrays\n");
  return;
 }   
 for( int iBin = 0; iBin <= fn_bin_total; iBin++ )
  (this->fArray)[iBin] = (Array.fArray)[iBin] ;
}


TArray_7 TArray_7::operator+( TArray_7& Array )
{ 
  TArray_7* temp = new TArray_7( this->fn_bin_x,
				 this->fn_bin_y,
				 this->fn_bin_z,
				 this->fn_bin_t,
				 this->fn_bin_i,
				 this->fn_bin_j,
				 this->fn_bin_k
				 ) ;
  if (
      ( this->fn_bin_x != Array.fn_bin_x ) ||
      ( this->fn_bin_y != Array.fn_bin_y ) ||
      ( this->fn_bin_z != Array.fn_bin_z ) ||
      ( this->fn_bin_t != Array.fn_bin_t ) ||
      ( this->fn_bin_i != Array.fn_bin_i ) ||
      ( this->fn_bin_j != Array.fn_bin_j ) ||
      ( this->fn_bin_k != Array.fn_bin_k )
      )
    {
      printf("Different type of Arrays\n");
      return (TArray_7&)(*temp) ;
    } 

     for ( int ix = 1; ix <= fn_bin_x; ix++ )
      for ( int iy = 1; iy <= fn_bin_y; iy++ )
	for ( int iz = 1; iz <= fn_bin_z; iz++ )
	  for ( int it = 1; it <= fn_bin_t; it++)
	     for ( int ii = 1; ii <= fn_bin_i; ii++ )
	       for ( int ij = 1; ij <= fn_bin_j; ij++ )
		 for ( int ik = 1; ik <= fn_bin_k; ik++)
		   {
		     temp->Value( ix, iy, iz, it, ii, ij, ik ) = 
		       this->Value( ix, iy, iz, it, ii, ij, ik ) + 
		       Array.Value( ix, iy, iz, it, ii, ij, ik ) ;
		   }
  return (TArray_7)(*temp) ;
}		


TArray_7 TArray_7::operator/( TArray_7& Array )
{
  TArray_7* temp = new TArray_7( this->fn_bin_x,
				 this->fn_bin_y,
				 this->fn_bin_z,
				 this->fn_bin_t,
				 this->fn_bin_i,
				 this->fn_bin_j,
				 this->fn_bin_k
				 ) ;
 if (
      ( this->fn_bin_x != Array.fn_bin_x ) ||
      ( this->fn_bin_y != Array.fn_bin_y ) ||
      ( this->fn_bin_z != Array.fn_bin_z ) ||
      ( this->fn_bin_t != Array.fn_bin_t ) ||
      ( this->fn_bin_i != Array.fn_bin_i ) ||
      ( this->fn_bin_j != Array.fn_bin_j ) ||
      ( this->fn_bin_k != Array.fn_bin_k )
      )
    {
      printf("Different type of Arrays\n");
      return (TArray_7&)(*temp) ;
    } 

    
    for ( int ix = 1; ix <= fn_bin_x; ix++ )
      for ( int iy = 1; iy <= fn_bin_y; iy++ )
	for ( int iz = 1; iz <= fn_bin_z; iz++ )
	  for ( int it = 1; it <= fn_bin_t ; it++)
	     for ( int ii = 1; ii <= fn_bin_i; ii++ )
	       for ( int ij = 1; ij <= fn_bin_j; ij++ )
		 for ( int ik = 1; ik <= fn_bin_k; ik++)
		   {
		     if ( fabs(Array.Value( ix, iy, iz, it, ii, ij, ik )) > 1.0e-35 )
		       {
			 temp->Value( ix, iy, iz, it, ii, ij, ik ) = 
			   this->Value( ix, iy, iz, it, ii, ij, ik ) / 
			   Array.Value( ix, iy, iz, it, ii, ij, ik ) ;
		       }
		     else
		       temp->Value( ix, iy, iz, it, ii, ij, ik ) = 0. ;;
	    }
  return (TArray_7)(*temp) ;
}


TArray_7 TArray_7::operator*( TArray_7& Array )
{
  TArray_7* temp = new TArray_7( this->fn_bin_x,
				 this->fn_bin_y,
				 this->fn_bin_z,
				 this->fn_bin_t,
				 this->fn_bin_i,
				 this->fn_bin_j,
				 this->fn_bin_k
				 ) ;

  if (
      ( this->fn_bin_x != Array.fn_bin_x ) ||
      ( this->fn_bin_y != Array.fn_bin_y ) ||
      ( this->fn_bin_z != Array.fn_bin_z ) ||
      ( this->fn_bin_t != Array.fn_bin_t ) ||
      ( this->fn_bin_i != Array.fn_bin_i ) ||
      ( this->fn_bin_j != Array.fn_bin_j ) ||
      ( this->fn_bin_k != Array.fn_bin_k )
      )
    {
      printf("Different type of Arrays\n");
      return (TArray_7&)(*temp) ;
    } 
    
    for ( int ix = 1; ix <= fn_bin_x; ix++ )
      for ( int iy = 1; iy <= fn_bin_y; iy++ )
	for ( int iz = 1; iz <= fn_bin_z; iz++ )
	  for ( int it = 1; it <= fn_bin_t ; it++)
	     for ( int ii = 1; ii <= fn_bin_i; ii++ )
	       for ( int ij = 1; ij <= fn_bin_j; ij++ )
		 for ( int ik = 1; ik <= fn_bin_k; ik++)
		   {
		     temp->Value( ix, iy, iz, it, ii, ij, ik  ) = 
		       this->Value( ix, iy, iz, it, ii, ij, ik  ) * 
		       Array.Value( ix, iy, iz, it, ii, ij, ik  ) ;
		   }
  return (TArray_7)(*temp) ;
}


TArray_7 TArray_7::operator-( TArray_7& Array )
{
  TArray_7* temp = new TArray_7( this->fn_bin_x,
				 this->fn_bin_y,
				 this->fn_bin_z,
				 this->fn_bin_t,
				 this->fn_bin_i,
				 this->fn_bin_j,
				 this->fn_bin_k
				 ) ;

  if (
      ( this->fn_bin_x != Array.fn_bin_x ) ||
      ( this->fn_bin_y != Array.fn_bin_y ) ||
      ( this->fn_bin_z != Array.fn_bin_z ) ||
      ( this->fn_bin_t != Array.fn_bin_t ) ||
      ( this->fn_bin_i != Array.fn_bin_i ) ||
      ( this->fn_bin_j != Array.fn_bin_j ) ||
      ( this->fn_bin_k != Array.fn_bin_k )
      )
    {
      printf("Different type of Arrays\n");
      return (TArray_7&)(*temp) ;
    } 

    for ( int ix = 1; ix <= fn_bin_x; ix++ )
      for ( int iy = 1; iy <= fn_bin_y; iy++ )
	for ( int iz = 1; iz <= fn_bin_z; iz++ )
	  for ( int it = 1; it <= fn_bin_t ; it++)
	     for ( int ii = 1; ii <= fn_bin_i; ii++ )
	       for ( int ij = 1; ij <= fn_bin_j; ij++ )
		 for ( int ik = 1; ik <= fn_bin_k; ik++)
		   {
		     temp->Value( ix, iy, iz, it, ii, ij, ik  ) = 
		       this->Value( ix, iy, iz, it, ii, ij, ik  ) - 
		       Array.Value( ix, iy, iz, it, ii, ij, ik  ) ;
		   }
  return (TArray_7)(*temp) ;
}


TArray_7 TArray_7::operator-( )
{ 
  TArray_7* temp = new TArray_7( this->fn_bin_x,
				 this->fn_bin_y,
				 this->fn_bin_z,
				 this->fn_bin_t,
				 this->fn_bin_i,
				 this->fn_bin_j,
				 this->fn_bin_k
				 ) ;
    
    for ( int ix = 1; ix <= fn_bin_x; ix++ )
      for ( int iy = 1; iy <= fn_bin_y; iy++ )
	for ( int iz = 1; iz <= fn_bin_z; iz++ )
	  for ( int it = 1; it <= fn_bin_t ; it++)
	     for ( int ii = 1; ii <= fn_bin_i; ii++ )
	       for ( int ij = 1; ij <= fn_bin_j; ij++ )
		 for ( int ik = 1; ik <= fn_bin_k; ik++)
		   {
		     temp->Value( ix, iy, iz, it, ii, ij, ik  ) = -1. * 
		       this->Value( ix, iy, iz, it, ii, ij, ik  ) ;
		   }
  return (TArray_7)(*temp) ;
}


float& TArray_7::Value( int ix, int iy, int iz, int it , int ii , int ij , int ik)
{
 float Temp = 0.;
 if (
      ( ix < 1 ) || ( ix > fn_bin_x ) ||
      ( iy < 1 ) || ( iy > fn_bin_y ) ||
      ( iz < 1 ) || ( iz > fn_bin_z ) ||
      ( it < 1 ) || ( it > fn_bin_t ) ||
      ( ii < 1 ) || ( ii > fn_bin_i ) ||
      ( ij < 1 ) || ( ij > fn_bin_j ) ||
      ( ik < 1 ) || ( ik > fn_bin_k )
    )
 {
  printf("**7-Dim Array is out of bounds**\a\n");
  return ( float& )  fArray[fn_bin_total] ;
 }   
 int iBin = ( ix - 1 ) * ( fn_bin_y * fn_bin_z * fn_bin_t * fn_bin_i * fn_bin_j * fn_bin_k ) + 
            ( iy - 1 ) * (            fn_bin_z * fn_bin_t * fn_bin_i * fn_bin_j * fn_bin_k ) +
            ( iz - 1 ) * (                       fn_bin_t * fn_bin_i * fn_bin_j * fn_bin_k ) +
            ( it - 1 ) * (                                  fn_bin_i * fn_bin_j * fn_bin_k ) +
            ( ii - 1 ) * (                                             fn_bin_j * fn_bin_k ) +
            ( ij - 1 ) * (                                                        fn_bin_k ) +
            ( ik - 1 )		                            ;
 return ( float& )  fArray[iBin] ;            
}
