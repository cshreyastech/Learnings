#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

int main ()
{
  char *tmp = (char *)malloc(128);
  int n=sprintf(tmp, "Hello from Chile.");

  string tmp_str = tmp;


  cout << *tmp << " : is a char array beginning with " <<n <<" chars long\n" << endl;
  cout << tmp_str << " : is a string with " <<n <<" chars long\n" << endl;

 free(tmp); 
 return 0;
}