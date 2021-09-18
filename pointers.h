/********************************************************************
***               Creation of Pointers routines                   ***
***                      30/03/2004                               ***
********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <assert.h>

double *create_double_pointer(int size)
{
  int i;
  double *pointer;
  
  assert(size>0);
  pointer=(double *)calloc(size,sizeof(double));
  if (pointer!=NULL)
    {
      for (i=0;i<size;++i) *(pointer+i)=0.0;
      return(pointer);
    }
  else {
    fprintf(stderr,"Error in routine create_double_pointer\n");
    exit(8);
  }
}

float *create_float_pointer(int size)
{
  int i;
  float *pointer;
  
  assert(size>0);
  pointer=(float *)calloc(size,sizeof(float));
  if (pointer!=NULL)
    {
      for (i=0;i<size;++i) *(pointer+i)=0.0;
      return(pointer);
    }
  else 
    {
      fprintf(stderr,"Error in routine create_float_pointer\n");
      exit(8);
    }
}

int *create_int_pointer(int size)
{
  int i;
  int *pointer;
  
  assert(size>0);
  pointer=(int *)calloc(size,sizeof(int));
  if (pointer!=NULL)
    {
      for (i=0;i<size;++i) *(pointer+i)=0;
      return(pointer);
    }
  else {
    fprintf(stderr,"Error in routine create_int_pointer\n");
    exit(8);
  }
}  

short int *create_short_int_pointer(int size)
{
  int i;
  short int *pointer;
  
  assert(size>0);
  pointer=(short int *)calloc(size,sizeof(short int));
  if (pointer!=NULL)
    {
      for (i=0;i<size;++i) *(pointer+i)=0;
      return(pointer);
    }
  else {
    fprintf(stderr,"Error in routine create_short_int_pointer\n");
    exit(8);
  }
}  

unsigned int *create_unsigned_int_pointer(int size)
{
  int i;
  unsigned int *pointer;
  
  assert(size>0);
  pointer=(unsigned int *)calloc(size,sizeof(unsigned int));
  if (pointer!=NULL)
    {
      for (i=0;i<size;++i) *(pointer+i)=0;
      return(pointer);
    }
  else {
    fprintf(stderr,"Error in routine create_unsigned_int_pointer\n");
    exit(8);
  }
}  

unsigned long *create_unsigned_long_pointer(int size)
{
  int i;
  unsigned long *pointer;
  
  assert(size>0);
  pointer=(unsigned long *)calloc(size,sizeof(unsigned long));
  if (pointer!=NULL)
    {
      for (i=0;i<size;++i) *(pointer+i)=0;
      return(pointer);
    }
  else {
    fprintf(stderr,"Error in routine create_unsigned_long_pointer\n");
    exit(8);
  }
} 

long *create_long_pointer(int size)
{
  int i;
  long *pointer;
  
  assert(size>0);
  pointer=(long *)calloc(size,sizeof(long));
  if (pointer!=NULL)
    {
      for (i=0;i<size;++i) *(pointer+i)=0;
      return(pointer);
    }
  else {
    fprintf(stderr,"Error in routine create_long_pointer\n");
    exit(8);
  }
}  

_Complex double *create_complex_double_pointer(int size)
{
  _Complex double *pointer;
  
  assert(size>0);
  pointer=(_Complex double *)calloc(size,sizeof(_Complex double));
  if (pointer!=NULL)
    return(pointer);
  else {
    fprintf(stderr,"Error in routine create_complex_double_pointer\n");
    exit(8);
  }
}


/********************************************************************
 *                    Change 1d pointer size                        * 
 *******************************************************************/
float *change_float_pointer_size(float *p,int size)
{
   float *pointer;
   
   assert(size>0);
   pointer=(float *)realloc(p,size*sizeof(float));
   if (pointer!=NULL)
     return(pointer);
   else
     {
       fprintf(stderr,"Error in routine change_float_pointer_size,\n");
       exit(8);
     }
}

double *change_double_pointer_size(double *p,int size)
{
  
  double *pointer;
  
  assert(size>0);
  pointer=(double *)realloc(p,size*sizeof(double));
  if (pointer!=NULL)
    return(pointer);
  else
    {
      
      fprintf(stderr,"Error in routine change_double_pointer_size,\n");
      exit(8);
    }
}




/********************************************************************
***               Creation of 2d Pointers routines                ***
***                      16/09/2004                               ***
********************************************************************/
int **create_2d_int_pointer(int x,int y)
{
  int **pointer;
  int i;
  
  assert((x>0) && (y>0));
  pointer = (int **)malloc(x*y * sizeof(int *));
  if (pointer==NULL)
    {
      fprintf(stderr,"Error in routine create_2d_int_pointer\n");
      exit(8);
    }
  else{
    for(i = 0; i < x; ++i)
      {
	pointer[i] = (int *)malloc(y * sizeof(int ));
	if (pointer[i]==NULL)
	  {
	    fprintf(stderr,"Error in routine create_2d_int_pointer\n");
	    exit(8);
	  }
      }
  }
  return(pointer);

}
/* modificada pelo heitor em 15 jun 15 */
int **create_2d_int_pointer_h(int x,int y)
{
  int **pointer;
  int i;
  
  assert((x>0) && (y>0));
  pointer = (int **)malloc(x* sizeof(int *));
  if (pointer==NULL)
    {
      fprintf(stderr,"Error in routine create_2d_int_pointer_h\n");
      exit(8);
    }
  else{
    for(i = 0; i < x; ++i)
      {
	pointer[i] = (int *)malloc(y * sizeof(int ));
	if (pointer[i]==NULL)
	  {
	    fprintf(stderr,"Error in routine create_2d_int_pointer_h\n");
	    exit(8);
	  }
      }
  }
  return(pointer);

}
short int **create_2d_short_int_pointer(int x,int y)
{
  short int **pointer;
  int i;
  
  assert((x>0) && (y>0));
  pointer = (short int **)malloc(x*y * sizeof(short int *));
  if (pointer==NULL)
    {
      fprintf(stderr,"Error in routine create_2d_short_int_pointer\n");
      exit(8);
    }
  else{
    for(i = 0; i < x; ++i)
      {
	pointer[i] = (short int *)malloc(y * sizeof(short int ));
	if (pointer[i]==NULL)
	  {
	    fprintf(stderr,"Error in routine create_2d_short_int_pointer\n");
	    exit(8);
	  }
      }
  }
  return(pointer);
}

unsigned int **create_2d_unsigned_int_pointer(int x,int y)
{
  unsigned int **pointer;
  int i;
  
  assert((x>0) && (y>0));
  pointer = (unsigned int **)malloc(x*y * sizeof(unsigned int *));
  if (pointer==NULL)
    {
      fprintf(stderr,"Error in routine create_2d_unsigned_int_pointer\n");
      exit(8);
    }
  else{
    for(i = 0; i < x; ++i)
      {
	pointer[i] = (unsigned int *)malloc(y * sizeof(unsigned int ));
	if (pointer[i]==NULL)
	  {
	    fprintf(stderr,"Error in routine create_2d_unsigned_int_pointer\n");
	    exit(8);
	  }
      }
  }
  return(pointer);
}

unsigned long **create_2d_unsigned_long_pointer(int x,int y)
{
   
     unsigned long **pointer;
     int i;
   
     assert((x>0) && (y>0));
     pointer = (unsigned long **)malloc(x*y * sizeof(unsigned long *));
     if (pointer==NULL)
     {
       
       fprintf(stderr,"Error in routine create_2d_unsigned_long_pointer\n");
       exit(8);
     }
     
     else
       {
	 
	 for(i = 0; i < x; ++i)
	   {
	     
	     pointer[i] = (unsigned long *)malloc(y * sizeof(unsigned long ));
	     if (pointer[i]==NULL)
	       {
		 
		 fprintf(stderr,"Error in routine create_2d_unsigned_long_pointer\n");
		 exit(8);
	       }
	   }
       }
     
     return(pointer);
}

long int **create_2d_long_int_pointer(int x,int y)
{
  long int **pointer;
  int i;
  
  assert((x>0) && (y>0));
  pointer = (long int **)malloc(x*y * sizeof(long int *));
  if (pointer==NULL)
    {
      fprintf(stderr,"Error in routine create_2d_long_int_pointer\n");
      exit(8);
    }
  else{
    for(i = 0; i < x; ++i)
      {
	pointer[i] = (long int *)malloc(y * sizeof(long int ));
	if (pointer[i]==NULL)
	  {
	    fprintf(stderr,"Error in routine create_2d_long_int_pointer\n");
	    exit(8);
	  }
      }
  }
  return(pointer);
}

float **create_2d_float_pointer(int x,int y)
{
  float **pointer;
  int i;
  
  assert((x>0) && (y>0));
  pointer = (float **)malloc(x*y * sizeof(float *));
  if (pointer==NULL)
    {
      fprintf(stderr,"Error in routine create_2d_float_pointer\n");
      exit(8);
    }
  else{
    for(i = 0; i < x; ++i)
      {
	pointer[i] = (float *)malloc(y * sizeof(float ));
	if (pointer[i]==NULL)
	  {
	    fprintf(stderr,"Error in routine create_2d_float_pointer\n");
	    exit(8);
	  }
      }
  }
  return(pointer);
}

double **create_2d_double_pointer(int x,int y)
{
  double **pointer;
  int i;
  
  assert((x>0) && (y>0));
  pointer = (double **)malloc(x*y * sizeof(double *));
  if (pointer==NULL)
    {
      fprintf(stderr,"Error in routine create_2d_double_pointer\n");
      exit(8);
    }
  else
    {
      for(i = 0; i < x; ++i)
	{
	  pointer[i] = (double *)malloc(y * sizeof(double ));
	  if (pointer[i]==NULL)
	    {
	      fprintf(stderr,"Error in routine create_2d_double_pointer\n");
	      exit(8);
	    }
	}
    }
  return(pointer);
}


void free_2d_int_pointer(int **pointer,int x, int y)
{
  int i;
  
  assert((x>0) && (y>0));
  for(i = 0; i < x; ++i)
    free(pointer[i]);
  free(pointer);
  return;
}

void free_2d_short_int_pointer(short int **pointer,int x, int y)
{
  int i;
  
  assert((x>0) && (y>0));
  for(i = 0; i < x; ++i)
    free(pointer[i]);
  free(pointer);
  return;
}

void free_2d_unsigned_int_pointer(unsigned int **pointer,int x, int y)
{
  int i;
  
  assert((x>0) && (y>0));
  for(i = 0; i < x; ++i)
    free(pointer[i]);
  free(pointer);
  return;
}


void free_2d_unsigned_long_pointer(unsigned long **pointer,int x, int y)
{
  int i;
  
  assert((x>0) && (y>0));
  for(i = 0; i < x; ++i)
    free(pointer[i]);
  free(pointer);
  return;
}

void free_2d_float_pointer(float **pointer,int x, int y)
{
  int i;
  
  assert((x>0) && (y>0));
  for(i = 0; i < x; ++i)
    free(pointer[i]);
  free(pointer);
  return;
}

void free_2d_double_pointer(double **pointer,int x, int y)
{
   
     int i;
   
     assert((x>0) && (y>0));
     for(i = 0; i < x; ++i)
         free(pointer[i]);
     free(pointer);
     return;
}





/********************************************************************
***               Creation of 3d Pointers routines                ***
***                      16/09/2004                               ***
********************************************************************/
int ***create_3d_int_pointer(int x,int y,int z)
{
  int ***pointer;
  int i,j;
  
  assert((x>0) && (y>0) && (z>0));
  pointer = (int ***)malloc(x*y*z * sizeof(int **));
  if (pointer==NULL)
    {
      fprintf(stderr,"Error in routine create_3d_int_pointer\n");
      exit(8);
    }
  else{
    for(i = 0; i < x; i++)
      {
	pointer[i] = (int **)malloc(y*z * sizeof(int *));
	if (pointer[i]==NULL)
	  {
	    fprintf(stderr,"Error in routine create_3d_int_pointer\n");
	    exit(8);
	  }
      }
    for(i = 0; i < x; i++)
      for(j = 0; j < y; j++)
	{
	  pointer[i][j] = (int *)malloc(z * sizeof(int));
	  if (pointer[i][j]==NULL)
	    {
	      fprintf(stderr,"Error in routine create_3d_int_pointer\n");
	      exit(8);
	    }
	}
  }
  return(pointer);
}


unsigned int ***create_3d_unsigned_int_pointer(int x,int y,int z)
{
  unsigned int ***pointer;
  unsigned int i,j;
  
  assert((x>0) && (y>0) && (z>0));
  pointer = (unsigned int ***)malloc(x*y*z * sizeof(unsigned int **));
  if (pointer==NULL)
    {
      fprintf(stderr,"Error in routine create_3d_unsigned_int_pointer\n");
      exit(8);
    }
  else{
    for(i = 0; i < x; i++)
      {
	pointer[i] = (unsigned int **)malloc(y*z * sizeof(unsigned int *));
	if (pointer[i]==NULL)
	  {
	    fprintf(stderr,"Error in routine create_3d_unsigned_int_pointer\n");
	    exit(8);
	  }
      }
    for(i = 0; i < x; i++)
      for(j = 0; j < y; j++)
	{
	  pointer[i][j] = (unsigned int *)malloc(z * sizeof(unsigned int));
	  if (pointer[i][j]==NULL)
	    {
	      fprintf(stderr,"Error in routine create_3d_unsigned_int_pointer\n");
	      exit(8);
	    }
	}
  }
  return(pointer);
}
double ***create_3d_double_pointer(int x,int y,int z)
{
  double ***pointer;
  int i,j;
  
  assert((x>0) && (y>0) && (z>0));
  pointer = (double ***)malloc(x*y*z * sizeof(double **));
  if (pointer==NULL)
    {
      fprintf(stderr,"Error in routine create_3d_double_pointer\n");
      exit(8);
    }
  else{
    for(i = 0; i < x; i++)
      {
	pointer[i] = (double **)malloc(y*z * sizeof(double *));
	if (pointer[i]==NULL)
	  {
	    fprintf(stderr,"Error in routine create_3d_double_pointer\n");
	    exit(8);
	  }
      }
    for(i = 0; i < x; i++)
      for(j = 0; j < y; j++)
	{
	  pointer[i][j] = (double *)malloc(z * sizeof(double));
	  if (pointer[i][j]==NULL)
	    {
	      fprintf(stderr,"Error in routine create_3d_double_pointer\n");
	      exit(8);
	    }
	}
  }
  return(pointer);
}



void free_3d_int_pointer(int ***pointer,int x,int y,int z)
     
{
  int i,j; 
  
  assert((x>0) && (y>0) && (z>0));
  for(i = 0; i < x; ++i)
    for(j=0; j < y; ++j)
      free(pointer[i][j]);
  for(i = 0; i < x; ++i)
    free(pointer[i]);
  free(pointer);
  return;
}

void free_3d_unsigned_int_pointer(unsigned int ***pointer,int x,int y,int z)
     
{
  int i,j; 
  
  assert((x>0) && (y>0) && (z>0));
  for(i = 0; i < x; ++i)
    for(j=0; j < y; ++j)
      free(pointer[i][j]);
  for(i = 0; i < x; ++i)
    free(pointer[i]);
  free(pointer);
  return;
}
 
void free_3d_double_pointer(double ***pointer,int x,int y,int z)
     
{
  int i,j; 
  
  assert((x>0) && (y>0) && (z>0));
  for(i = 0; i < x; ++i)
    for(j=0; j < y; ++j)
      free(pointer[i][j]);
  for(i = 0; i < x; ++i)
    free(pointer[i]);
  free(pointer);
  return;
}
