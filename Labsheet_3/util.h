// this #ifndef stops this file
// from being included mored than
// once by the compiler. 
#ifndef _UTIL_H
#define _UTIL_H

class Util_c {
  public:

    Util_c() {

    } 

void initialize()
{
  
}

void insertionSort(unsigned long array[], int n) 
{ 
  int i, element, j; 
  for (i = 1; i < n; i++) 
  { 
    element = array[i]; 
    j = i - 1; 
    while (j >= 0 && array[j] > element) 
    { 
      array[j + 1] = array[j]; 
      j = j - 1; 
    } 
  array[j + 1] = element; 
  } 
}  

void printArray(unsigned long array[], int n) 
{ 
  int i; 
  Serial.println("BEGIN PRINTING");
  for (i = 0; i < n; i++) 
  {
    Serial.println(array[i]); 
  }
}

#endif
