/*
Change the following program by executing the thread() function in its own 
thread created in main(). The program should calculate the total and write 
it to the standard output stream twice. The implementation of calculate(), 
print() and thread() can be modified however, the signature of each 
function needs to stay the same. In other words, each function should 
still neither require any parameters nor return a value.
*/

#include <iostream> 

int sum = 0; 

void calculate() 
{ 
  for (int i = 0; i < 1000; ++i) 
    sum += i; 
} 

void print() 
{ 
  std::cout << sum << std::endl; 
} 

void thread() 
{ 
  calculate(); 
  print(); 
} 

int main() 
{ 
  thread(); 
} 