// Modified exercise from Hal Perkins, CSE333 at UWashington

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


// A vector of element_t's
typedef struct vector_t{
  size_t length;
  int *arry;
} *vector_t;


// Malloc memory for a vector of size n
vector_t VectorCreate(size_t n);

// Set (index)th element of v to be e
void VectorSet(vector_t v, uint32_t index, int *e);

// Returns the (index)th element of v
int VectorGet(vector_t v, uint32_t index);

// Returns the length of v. Assume v != NULL
size_t VectorLength(vector_t v);

// Returns a copy of arry with new length newLen. If newLen < oldLen
// then returned array is clipped. If newLen > oldLen, then the 
// resulting array will be padded with 0
int *ResizeArray(int *arry, size_t oldLen, size_t newLen);

//Print the elements of a vector assuming they are ints
void PrintIntVector(vector_t v);

#define N 10
int main(int argc, char **argv){
  uint32_t i;
  vector_t v = VectorCreate(4);

  for(i = 0; i < N; ++i){
    int *x = (int*) malloc(sizeof(int));
    VectorSet(v, i, x);
  }

  PrintIntVector(v);
}

vector_t VectorCreate(size_t n){
  vector_t v = (vector_t) malloc(sizeof(struct vector_t));
  v->arry = (int *) malloc(n*sizeof(int));

  return v;
}

void VectorFree(vector_t v){
  assert(v != NULL);
  free(v->arry);
  free(v);
}

void VectorSet(vector_t v, uint32_t index, int *e){
  assert(v != NULL);

  if(index >= v->length){
    size_t newLength = index+1;
    v->arry = ResizeArray(v->arry, v->length, newLength);
    v->length = newLength;
  }
  
  v->arry[index] = *e;
}


int VectorGet(vector_t v, uint32_t index){
  assert(v != NULL);
  return v->arry[index];
}

size_t VectorLength(vector_t v){
  assert(v != NULL);
  return v->length;
}

int *ResizeArray(int *arry, size_t oldLen, size_t newLen){
  assert(arry != NULL);

  uint32_t i;
  size_t copyLen = oldLen > newLen ? newLen : oldLen;

  int *newArry = (int *) malloc(newLen*sizeof(int));

  // Copy elements to new array
  for(i = 0; i < copyLen; ++i){
    newArry[i] = arry[i];
  }

  // Initalize rest of array to 0
  for(i = copyLen; i < newLen; ++i){
    newArry[i] = 0;
  }

  return newArry;
}

void PrintIntVector(vector_t v){
  assert(v != NULL);
  
  uint32_t i;
  size_t length = VectorLength(v);

  if(length == 0) return;

  printf("[");
  for(i = 0; i < length; ++i){
    printf("%d", VectorGet(v, i));
    if(i != length-1){
      printf(", ");
    }
  }
  printf("]\n");
}

