#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "DynamicString.h"

typedef enum {
  HEAP_OK,
  HEAP_FAIL
}HEAP_RETURN_CODE;

HEAP_RETURN_CODE heap_insert(DArray* heapArray, int heapSize, int insertData);
HEAP_RETURN_CODE heap_delete(DArray* heapArray, int heapSize, int* returnData);
HEAP_RETURN_CODE heap_sort(DArray* heapArray, int heapSize);

void swap(int *src, int *dst);
void printArray(DArray *input);
void testDArray();
int minChild(DArray* heapArray, int idx);

int main(int argc, char** argv){
  DArray *input = ArrayNew();
  int idx = 0;
  int a = 0;

  srand(time(NULL));
  for(idx = 0; idx < 20; idx++){
    heap_insert(input, input->len, (rand()%20)+1);
  }
  printArray(input);

  for(idx = 0; idx < 20; idx++){
    heap_delete(input, input->len, &a);
    printf("Pop : %d \n", a);
  }

  return 0;
}

void testDArray(){

  DArray *input = ArrayNew();
  int idx = 0;
  
  if( input == NULL ){
    printf("Allocate dynamic array error ... \n");
    return;
  }

  for(idx = 0; idx < 10; idx++){
    ArrayAppend(input, idx);
    printArray(input); 
  }
  
  for(idx = 0; idx < 15; idx++){
    printf("Pop : %d \n", ArrayPopFirst(input));
    printArray(input);
  }

  for(idx = 0; idx < 10; idx++){
    ArrayAppend(input, idx);
    printArray(input); 
  }

  for(idx = 0; idx < 15; idx++){
    printf("Pop : %d \n", ArrayPopFirst(input));
    printArray(input);
  }

  return;
}

void printArray(DArray *input){
  int idx = 0;

  printf("Array (%d) [ ", input->len);
  for( idx = 1; idx <= input->len; idx++){
    printf("%d ", input->s[idx]);
  }
  printf("] , size : %d \n", input->size);

  return;
}

HEAP_RETURN_CODE heap_insert(DArray* heapArray, int heapSize, int insertData){
  HEAP_RETURN_CODE rc = HEAP_FAIL;
  int idx = 0, child_idx = 0;
  int tmp = 0;
  
  if( heapArray == NULL ){
    return HEAP_FAIL;
  }

  ArrayAppend(heapArray, insertData);

  // Sorting
  idx = heapArray->len / 2;
  child_idx = heapArray->len;
  while(idx){
    
    tmp = heapArray->s[idx];
    if( heapArray->s[child_idx] < tmp ){
      //swap( &heapArray->s[idx], &heapArray->s[heapArray->len] );
      heapArray->s[idx] = heapArray->s[child_idx];
      heapArray->s[child_idx] = tmp;
    }

    child_idx = child_idx / 2;
    idx = idx / 2;
  }  

  return rc;
}

HEAP_RETURN_CODE heap_delete(DArray* heapArray, int heapSize, int* returnData){
  HEAP_RETURN_CODE rc = HEAP_FAIL;
  int idx = 1;
  int tmp = 0;
  int mc = 0;

  if(heapArray == NULL || heapSize == 0){
    return HEAP_FAIL;
  }

  *returnData = heapArray->s[1];
  heapArray->s[1] = heapArray->s[heapArray->len];
  heapArray->len--;

  while( (idx*2) <= heapArray->len ){

    mc = minChild(heapArray, idx);
    if( heapArray->s[idx] > heapArray->s[mc] ){
      tmp = heapArray->s[mc];
      heapArray->s[mc] = heapArray->s[idx];
      heapArray->s[idx] = tmp;
    }

    idx = mc;
  }

  return HEAP_OK;
}

HEAP_RETURN_CODE heap_sort(DArray* heapArray, int heapSize);


int minChild(DArray* heapArray, int idx){
  int currentSize = heapArray->len;

  if( (idx * 2 + 1) > currentSize){
    return idx*2;
  } else {
    if( heapArray->s[idx*2] < heapArray->s[idx*2+1] ){
      return idx * 2;
    } else {
      return idx * 2 + 1;
    }
  }
}
