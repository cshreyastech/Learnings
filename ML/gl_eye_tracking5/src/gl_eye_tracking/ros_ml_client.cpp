
#include "gl_eye_tracking/ros_ml_client.h"


RosMLClient::RosMLClient() : olc::GameEngine()
{
	ML_LOG_TAG(Debug, APP_TAG, "inside RosMLClient::RosMLClient()");
	sAppName = "MMO Client";
}

RosMLClient::~RosMLClient()
{
	ML_LOG_TAG(Debug, APP_TAG, "inside ~RosMLClient()");
	// delete[] vertices;
}

bool RosMLClient::OnUserCreate()
{

	return false;
}

bool RosMLClient::OnUserUpdate(float fElapsedTime)
{
	// Check for incoming network messages
	ML_LOG_TAG(Debug, APP_TAG, "inside RosMLClient::OnUserUpdate()");
	return true;
}

void RosMLClient::Deserialize(const char* data, float vertices[], const int vertices_length)
{
  float *q = (float*)data;
  for(int i = 0; i < vertices_length; i++)
  {
    vertices[i] = *q; q++;
  }
}

int main()
{
	RosMLClient ros_ml_client;
	if (ros_ml_client.Construct(800, 600))
		ros_ml_client.Start();
	return 0;
}