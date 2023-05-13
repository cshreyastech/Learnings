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

  /// TBD
  // std::string test_string1 = "Hello World";
  // int test_string1_len = test_string1.length();
  // char m_Test[test_string1_len];
  // strcpy( (char*) m_Test, test_string1.c_str() );
  // int m_Test_len = sizeof(m_Test) / sizeof(m_Test[0]);
  // for(int i = 0; i < m_Test_len; i++)
  // {
  //   printf("m_Test[%d]=%c\n", i, m_Test[i]);
  // }

  // std::string test_string2 = convertToString(m_Test, m_Test_len);
  // std::cout << "Compare test_string: " 
  //           << test_string1.compare(test_string2) 
  //           << std::endl;





  // Transformation t_w_e;
  // t_w_e.i = 10; t_w_e.f = -10.12345f;
  // t_w_e.t = glm::vec4(0.923984f, .0f, 1.0f, 1.0f);

  Transformation t_w_e;
  t_w_e.i = 10; t_w_e.f = -10.12345f;
  t_w_e.t = glm::vec4(0.923984f, .0f, 1.0f, 1.0f);
  // printf("i: %d, f: %f, t[%f], t[%f], t[%f], t[%f]\n", 
  //   t_w_e.i, t_w_e.f, t_w_e.t[0], t_w_e.t[1], t_w_e.t[2], t_w_e.t[3]);

  std::string serilized_t_w_e_str1 = serialize<Transformation>(t_w_e);

  int serilized_t_w_e_str1_len = serilized_t_w_e_str1.length();
  std::cout << "serilized_t_w_e_str1_len: " << serilized_t_w_e_str1_len << std::endl;

  int serilized_t_w_e_array_len = serilized_t_w_e_str1_len * sizeof(Transformation);
  char serilized_t_w_e_array[serilized_t_w_e_array_len];
  strcpy( (char*) serilized_t_w_e_array, serilized_t_w_e_str1.c_str() );


  // serilized_t_w_e_array[serilized_t_w_e_str1_len] = '\0';
  // // for(int i = 0; i < serilized_t_w_e_str1_len; i++)
  // // {
  // //   printf("serilized_t_w_e_array[%d]=%c\n", i, serilized_t_w_e_array[i]);
  // // }
  // std::cout << "serilized_t_w_e_array: " << serilized_t_w_e_array << std::endl;

  std::string serilized_t_w_e_str2 = 
    convertToString(serilized_t_w_e_array, serilized_t_w_e_array_len);
  std::string serilized_t_w_e_str3 = convertToString(serilized_t_w_e_array);
  std::string serilized_t_w_e_str4 = convertToString2(serilized_t_w_e_array);
  std::string serilized_t_w_e_str5(reinterpret_cast<char*>(serilized_t_w_e_array));
  std::string serilized_t_w_e_str6(serilized_t_w_e_array);
  
  std::cout << "Compare test_string1: " 
            << serilized_t_w_e_str1.compare(serilized_t_w_e_str1) 
            << std::endl;

  std::cout << "Compare test_string2: " 
            << serilized_t_w_e_str1.compare(serilized_t_w_e_str2) 
            << std::endl;

  std::cout << "Compare test_string3: " 
            << serilized_t_w_e_str1.compare(serilized_t_w_e_str3) 
            << std::endl;

  std::cout << "Compare test_string4: " 
            << serilized_t_w_e_str1.compare(serilized_t_w_e_str4) 
            << std::endl;

  std::cout << "Compare test_string5: " 
            << serilized_t_w_e_str1.compare(serilized_t_w_e_str5) 
            << std::endl;

  std::cout << "Compare test_string6: " 
            << serilized_t_w_e_str1.compare(serilized_t_w_e_str6) 
            << std::endl;



  // Transformation t_w_e2 = deserialize<Transformation>(serilized_t_w_e_array, false);

  // strcpy(reinterpret_cast<char*>(serilized_t_w_e_unsigned_array), serilized_t_w_e_str1.c_str());

  // for(int i = 0; i < sizeof_dims; i++)
  // {
  //   printf("serilized_t_w_e_unsigned_array[%d]=%c\n", i, serilized_t_w_e_unsigned_array[i]);
  // }
  // // ----
  // int image_size = sizeof_dims; //eye_track_dims_ + 1;

  // std::string serilized_t_w_e_str2;
  // //= convertToString(serilized_t_w_e_unsigned_array, image_size);
  // //(const char*)serilized_t_w_e_unsigned_array;
  // // strcpy(reinterpret_cast<char*>(serilized_t_w_e_str2), serilized_t_w_e_unsigned_array);
  // // printf("serilized_string length1: %ld\n", serilized_t_w_e_str1.length());
  // // printf("serilized_string length2: %ld\n", serilized_t_w_e_str2.length());

  // // std::cout << "Compare serilized strings: " 
  // //           << serilized_t_w_e_str1.compare(serilized_t_w_e_str2) 
  // //           << std::endl;



  // // Transformation t_w_e2 = deserialize<Transformation>(serilized_struct, false);
  // // printf("i: %d, f: %f, t[%f], t[%f], t[%f], t[%f]\n", 
  // //   t_w_e2.i, t_w_e2.f, t_w_e2.t[0], t_w_e2.t[1], t_w_e2.t[2], t_w_e2.t[3]);

  // // printf("serilized_struct:%s, len: %ld\n", serilized_struct.c_str(), serilized_struct.length());





  return 0;
}