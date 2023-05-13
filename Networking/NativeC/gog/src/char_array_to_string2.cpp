#include <string>
#include <iostream>
#include <array>
 
int main()
{
  // initialize a char array with "hello\0";
  std::array<char, 6> bar{"hello"};
  // create a string from it using the .data() ptr,
  // this uses the `const char*` ctor of the string
  std::string myString(bar.data());
  // output
  std::cout << myString << std::endl;

  return 0;
}