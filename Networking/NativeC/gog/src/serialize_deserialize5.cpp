// https://stackoverflow.com/questions/16543519/serialization-of-struct
#include <iostream>
#include <cstring>
#include "gog/struct_declarations.hpp"
#include <stdio.h>

#define BUFSIZE 512
// #define PACKETSIZE sizeof(Transformation3)

using namespace std;


void serialize(Transformation3* msgPacket, unsigned char *data);
void deserialize(unsigned char *data, Transformation3* msgPacket);
void printMsg(Transformation3* msgPacket);

int main()
{
  Transformation3 newMsg;
  newMsg.q_w_eye = { 0.608286f, -0.440174f, 0.500542f, 0.430921f };
  newMsg.p_w_eye = { 0.518250f, -0.402129f, -0.456791f };

  printMsg(&newMsg);

  const int packet_size = sizeof(Transformation3);
  unsigned char data[packet_size];

  serialize(&newMsg, data);
 
  Transformation3 temp;
  deserialize(data, &temp);
  printMsg(&temp);
  return 0;
}

void serialize(Transformation3* msgPacket, unsigned char *data)
{
  float *q = (float*)data;

  glm::quat q_w_eye = msgPacket->q_w_eye;
  *q = q_w_eye[0]; q++;
  *q = q_w_eye[1]; q++;
  *q = q_w_eye[2]; q++;
  *q = q_w_eye[3]; q++;

  glm::vec p_w_eye = msgPacket->p_w_eye;
  *q = p_w_eye[0]; q++;
  *q = p_w_eye[1]; q++;
  *q = p_w_eye[2]; q++;
}

void deserialize(unsigned char *data, Transformation3* msgPacket)
{
  float *q = (float*)data;
  msgPacket->q_w_eye[0] = *q; q++;
  msgPacket->q_w_eye[1] = *q; q++;
  msgPacket->q_w_eye[2] = *q; q++;
  msgPacket->q_w_eye[3] = *q; q++;

  msgPacket->p_w_eye[0] = *q; q++;
  msgPacket->p_w_eye[1] = *q; q++;
  msgPacket->p_w_eye[2] = *q; q++;
}

void printMsg(Transformation3* msgPacket)
{
  printf("q_w_eye: (%f, %f, %f, %f)\n", 
    msgPacket->q_w_eye[0], msgPacket->q_w_eye[1], msgPacket->q_w_eye[2], msgPacket->q_w_eye[3]);
  printf("p_w_eye: (%f, %f, %f)\n", 
  msgPacket->p_w_eye[0], msgPacket->p_w_eye[1], msgPacket->p_w_eye[2]);
}