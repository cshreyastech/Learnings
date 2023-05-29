#include <string>
#include <cstring>
#include <gog/struct_declarations.hpp>
#include <iostream>
#include <bits/stdc++.h>
#include <algorithm>


/*
 * Convert a packet into a byte string.
 */
template <typename PacketType>
std::string serialize(PacketType &packet)
{
  auto ptr = reinterpret_cast<char*>(&packet);
  return std::string(ptr, ptr + sizeof packet);
}

// https://codereview.stackexchange.com/questions/260597/de-serialization-of-structs-representing-tcp-messages
/*
 * Convert a byte string into a packet.
 */
template <typename PacketType>
PacketType deserialize(std::string &buf, bool partialProcessing = false)
{
  PacketType packet;
  size_t bufSize = buf.length();
  size_t packetSize = sizeof packet;

  if (packetSize > bufSize)
      std::cerr << "Packet larger than buffer size. Partial read: " << (packetSize - bufSize) << std::endl;

  if (packetSize < bufSize && !partialProcessing)
      std::cerr << "Packet smaller than buffer size. Bytes unprocessed: " << (bufSize - packetSize) << std::endl;

  auto ptr = reinterpret_cast<char*>(&buf[0]);
  std::memcpy(&packet, ptr, (packetSize < bufSize) ? packetSize : bufSize);
  return packet;
}

std::string convertToString(char* a, int size)
{
  int i;
  std::string s = "";
  for (i = 0; i < size; i++) {
      s = s + a[i];
  }
  return s;
}

std::string convertToString(char* a)
{
  std::string s(a);

  // we cannot use this technique again
  // to store something in s
  // because we use constructors
  // which are only called
  // when the string is declared.

  // Remove commented portion
  // to see for yourself

  /*
  char demo[] = "gfg";
  s(demo); // compilation error
  */

  return s;
}

std::string convertToString2(char* a)
{
  std::string s = a;
  return s;
}

int main()
{
  // Transformation1 t1_w_e;
  // t1_w_e.i = 10; 
  // std::cout << "t1_w_e1: " << t1_w_e.i << std::endl;

  // std::string serilized_t1_w_e_str1 = serialize<Transformation1>(t1_w_e);

  // int serilized_t1_w_e_str1_len = serilized_t1_w_e_str1.length();
  // std::cout << "serilized_t1_w_e_str1_len: " << serilized_t1_w_e_str1_len << std::endl;

  // int serilized_t1_w_e_array_len = serilized_t1_w_e_str1_len * sizeof(Transformation1);
  // char serilized_t1_w_e_array[serilized_t1_w_e_array_len];
  // strcpy( (char*) serilized_t1_w_e_array, serilized_t1_w_e_str1.c_str() );

  // Transformation1 t1_w_e2 = deserialize<Transformation1>(serilized_t1_w_e_str1, false);
  // std::cout << "t1_w_e2: " << t1_w_e2.i << std::endl;



  // std::string s1 = "geeksforgeeks";
  // char* char_arr = s1.data();
  // std::string s2(char_arr);
  // std::cout << s1 << std::endl;
  // std::cout << s2 << std::endl;

  Transformation t_w_e;
  t_w_e.i = 10; 
  std::cout << "t_w_e1: " << t_w_e.i << std::endl;

  std::string serilized_t_w_e_str1 = serialize<Transformation>(t_w_e);

  const int serilized_t_w_e_str1_len = serilized_t_w_e_str1.length();
  

  char* serilized_t_w_e_array = serilized_t_w_e_str1.data();

  for(int i = 0; i < serilized_t_w_e_str1_len; i++)
  {
    std::cout << serilized_t_w_e_array[i] << std::endl;    
  }

  std::string serilized_t_w_e_str2(serilized_t_w_e_array);

  const int serilized_t_w_e_str2_len = serilized_t_w_e_str2.length();


  std::cout << "serilized_t_w_e_str1: " << serilized_t_w_e_str1 << std::endl;
  std::cout << "serilized_t_w_e_str2: " << serilized_t_w_e_str2 << std::endl;

  std::cout << "serilized_t_w_e_str1_len: " << serilized_t_w_e_str1_len << std::endl;
  std::cout << "serilized_t_w_e_str2_len: " << serilized_t_w_e_str2_len << std::endl;
  
  // Transformation t_w_e2 = deserialize<Transformation>(serilized_t_w_e_str2, false);
  // std::cout << "t_w_e2: " << t_w_e2.i << std::endl;



  return 0;
}