#ifndef _DYNAMIC_STRING_H_
#define _DYNAMIC_STRING_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX(a, b) ((a) > (b) ? a : b)

typedef struct DynamicString{
  int len;
  int size;
  char *s;
}DString;

typedef struct DynamicArray{
  int len;
  int size;
  int *s;
}DArray;

DString* StrNew();
void StrAppend(DString* str, char *s);

DArray* ArrayNew();
void ArrayAppend(DArray* str, int s);
int ArrayPopFirst(DArray* str);

#endif
