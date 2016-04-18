
#include <iostream.h> 
#include <stdio.h>
#include <math.h>
#include "TArray_4.h"

TArray_4::TArray_4( int n_x, int n_y, int n_z, int n_t )
{
 fn_bin_x = n_x;
 fn_bin_y = n_y;
 fn_bin_z = n_z;
 fn_bin_t = n_t;
 
 fn_bin_total = fn_bin_x * fn_bin_y * fn_bin_z * fn_bin_t ;
 
 fArray = new float[fn_bin_total+1] ;
}


TArray_4::TArray_4( const TArray_4& Array )
{
 this->fn_bin_x = Array.fn_bin_x;
 this->fn_bin_y = Array.fn_bin_y;
 this->fn_bin_z = Array.fn_bin_z;
 this->fn_bin_t = Array.fn_bin_t;
 
 this->fn_bin_total = Array.fn_bin_total ;
 
 this->fArray = new float[fn_bin_total+1] ; 
 
 for( int iBin = 0; iBin <= fn_bin_total; iBin++ )
  (this->fArray)[iBin] = (Array.fArray)[iBin] ;
}


TArray_4::~TArray_4()
{
 delete[] fArray;
}


void TArray_4::operator=( TArray_4& Array )
{
 if (
     ( this->fn_bin_x != Array.fn_bin_x ) ||
     ( this->fn_bin_y != Array.fn_bin_y ) ||
     ( this->fn_bin_z != Array.fn_bin_z ) ||
     ( this->fn_bin_t != Array.fn_bin_t ) 
    )
 {
  printf("Different type of Arrays\n");
  return;
 }   
 for( int iBin = 0; iBin <= fn_bin_total; iBin++ )
  (this->fArray)[iBin] = (Array.fArray)[iBin] ;
}


TArray_4 TArray_4::operator+( TArray_4& Array )
{ 
  TArray_4* temp = new TArray_4( this->fn_bin_x,
				 this->fn_bin_y,
				 this->fn_bin_z,
				 this->fn_bin_t
				 ) ;
  if (
      ( this->fn_bin_x != Array.fn_bin_x ) ||
      ( this->fn_bin_y != Array.fn_bin_y ) ||
      ( this->fn_bin_z != Array.fn_bin_z ) ||
      ( this->fn_bin_t != Array.fn_bin_t ) 
      )
    {
      printf("Different type of Arrays\n");
      return (TArray_4&)(*temp) ;
    } 

     for ( int ix = 1; ix <= fn_bin_x; ix++ )
      for ( int iy = 1; iy <= fn_bin_y; iy++ )
	for ( int iz = 1; iz <= fn_bin_z; iz++ )
	  for ( int it = 1; it <= fn_bin_t; it++)
	    {
	      temp->Value( ix, iy, iz, it ) = 
		this->Value( ix, iy, iz, it ) + 
		Array.Value( ix, iy, iz, it ) ;
	    }
  return (TArray_4)(*temp) ;
}		


TArray_4 TArray_4::operator/( TArray_4& Array )
{
  TArray_4* temp = new TArray_4( this->fn_bin_x,
				 this->fn_bin_y,
				 this->fn_bin_z,
				 this->fn_bin_t
				 ) ;
 if (
      ( this->fn_bin_x != Array.fn_bin_x ) ||
      ( this->fn_bin_y != Array.fn_bin_y ) ||
      ( this->fn_bin_z != Array.fn_bin_z ) ||
      ( this->fn_bin_t != Array.fn_bin_t ) 
      )
    {
      printf("Different type of Arrays\n");
      return (TArray_4&)(*temp) ;
    } 

    
    for ( int ix = 1; ix <= fn_bin_x; ix++ )
      for ( int iy = 1; iy <= fn_bin_y; iy++ )
	for ( int iz = 1; iz <= fn_bin_z; iz++ )
	  for ( int it = 1; it <= fn_bin_t ; it++)
	    {
	      if ( fabs(Array.Value( ix, iy, iz, it )) > 1.0e-35 )
		   {
		     temp->Value( ix, iy, iz, it ) = 
		       this->Value( ix, iy, iz, it ) / 
		       Array.Value( ix, iy, iz, it ) ;
		   }
	      else
		temp->Value( ix, iy, iz, it ) = 0. ;;
	    }
  return (TArray_4)(*temp) ;
}


TArray_4 TArray_4::operator*( TArray_4& Array )
{
  TArray_4* temp = new TArray_4( this->fn_bin_x,
				 this->fn_bin_y,
				 this->fn_bin_z,
				 this->fn_bin_t
				 ) ;

  if (
      ( this->fn_bin_x != Array.fn_bin_x ) ||
      ( this->fn_bin_y != Array.fn_bin_y ) ||
      ( this->fn_bin_z != Array.fn_bin_z ) ||
      ( this->fn_bin_t != Array.fn_bin_t ) 
      )
    {
      printf("Different type of Arrays\n");
      return (TArray_4&)(*temp) ;
    } 
    
    for ( int ix = 1; ix <= fn_bin_x; ix++ )
      for ( int iy = 1; iy <= fn_bin_y; iy++ )
	for ( int iz = 1; iz <= fn_bin_z; iz++ )
	  for ( int it = 1; it <= fn_bin_t ; it++)
	    {
	      temp->Value( ix, iy, iz, it ) = 
		this->Value( ix, iy, iz, it ) * 
		Array.Value( ix, iy, iz, it ) ;
	    }
  return (TArray_4)(*temp) ;
}


TArray_4 TArray_4::operator-( TArray_4& Array )
{
  TArray_4* temp = new TArray_4( this->fn_bin_x,
				 this->fn_bin_y,
				 this->fn_bin_z,
				 this->fn_bin_t
				 ) ;

  if (
      ( this->fn_bin_x != Array.fn_bin_x ) ||
      ( this->fn_bin_y != Array.fn_bin_y ) ||
      ( this->fn_bin_z != Array.fn_bin_z ) ||
      ( this->fn_bin_t != Array.fn_bin_t ) 
      )
    {
      printf("Different type of Arrays\n");
      return (TArray_4&)(*temp) ;
    } 

    for ( int ix = 1; ix <= fn_bin_x; ix++ )
      for ( int iy = 1; iy <= fn_bin_y; iy++ )
	for ( int iz = 1; iz <= fn_bin_z; iz++ )
	  for ( int it = 1; it <= fn_bin_t ; it++)
	    {
	      temp->Value( ix, iy, iz, it ) = 
		this->Value( ix, iy, iz, it ) - 
		Array.Value( ix, iy, iz, it ) ;
	    }
  return (TArray_4)(*temp) ;
}


TArray_4 TArray_4::operator-( )
{ 
  TArray_4* temp = new TArray_4( this->fn_bin_x,
				 this->fn_bin_y,
				 this->fn_bin_z,
				 this->fn_bin_t
				 ) ;
    
    for ( int ix = 1; ix <= fn_bin_x; ix++ )
      for ( int iy = 1; iy <= fn_bin_y; iy++ )
	for ( int iz = 1; iz <= fn_bin_z; iz++ )
	  for ( int it = 1; it <= fn_bin_t ; it++)
	    {
	      temp->Value( ix, iy, iz, it ) = -1. * 
		this->Value( ix, iy, iz, it ) ;
	    }
  return (TArray_4)(*temp) ;
}


float& TArray_4::Value( int ix, int iy, int iz, int it )
{
 float Temp = 0.;
 if (
      ( ix < 1 ) || ( ix > fn_bin_x ) ||
      ( iy < 1 ) || ( iy > fn_bin_y ) ||
      ( iz < 1 ) || ( iz > fn_bin_z ) ||
      ( it < 1 ) || ( it > fn_bin_t )
    )
 {
  printf("**4-Dim Array is out of bounds**\a\n");
  return ( float& )  fArray[fn_bin_total] ;
 }   
 int iBin = ( ix - 1 ) * ( fn_bin_y * fn_bin_z * fn_bin_t ) + 
            ( iy - 1 ) * (            fn_bin_z * fn_bin_t ) +
            ( iz - 1 ) * (                       fn_bin_t ) +
            ( it - 1 )		                            ;
 return ( float& )  fArray[iBin] ;            
}
