#include "DynamicString.h"

DString *StrNew() {
  DString *str = malloc(sizeof(DString));
  str->s = malloc(1);
  str->s[0] = '\0';
  str->len = 0;
  str->size = 1;

  return str;
}

void StrAppend(DString *str, char *s) {
  int newLen = str->len + strlen(s);
  if (newLen+1 > str->size) {
    int newSize = MAX(str->size*2, newLen+1);
    char *t = malloc(newSize);
    sprintf(t, "%s%s", str->s, s);
    free(str->s);
    str->s = t;
    str->len = newLen;
    str->size = newSize;
  } else {
    strcat(&str->s[str->len], s);
    str->len += strlen(s);
  }
}

DArray *ArrayNew() {
  DArray *array = malloc(sizeof(DArray));
  array->s = malloc(sizeof(int) * 2);
  array->s[0] = 0;
  array->s[1] = 0;
  array->len = 0;
  array->size = 2;

  return array;
}

DArray* ArrayNewHeap(int type){
  DArray *array = ArrayNew();

  if( type == MAX_HEAP ){
    array->heap_handler = maxHeap;
  } else if( type == MIN_HEAP ){
    array->heap_handler = minHeap;
  }

  return array;
}

int maxHeap(int* a, int* b){
  return ( *a > *b )? 1 : 0;
}

int minHeap(int* a, int* b){
  return ( *a < *b )? 1 : 0;
}

void ArrayAppend(DArray *str, int s) {
  int newLen = str->len + 1; //Assume only one integer come in

  if (str->len == 0) { 
    str->s[newLen] = s;
    str->len = newLen;

  } else if (newLen >= str->size) {
    int newSize = MAX(str->size*2, newLen);
    int *t = malloc(newSize * sizeof(int));

    memcpy( t, str->s, sizeof(int)*newLen );
    t[newLen] = s;
    free(str->s);
    str->s = t;
    str->len = newLen;
    str->size = newSize;

  } else {
    str->s[newLen] = s;
    str->len = newLen;
  }
}

int ArrayPopFirst(DArray *str){
  int target = str->s[1];
  int newLen = str->len - 1;

  if(str->len == 0){
    printf("Nothing in the DArray ... \n");
    return 0;
  }

  memmove( &str->s[1], &str->s[2], sizeof(int)*newLen);
  str->s[str->len] = 0;
  str->len = newLen;
  
  return target; 
}
