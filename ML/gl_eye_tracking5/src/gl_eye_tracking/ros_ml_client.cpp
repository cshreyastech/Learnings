
#include "gl_eye_tracking/ros_ml_client.h"

RosMLClient::RosMLClient() : olc::GameEngine()
{
	// std::cout << "RosMLClient::RosMLClient()\n";
	ML_LOG_TAG(Debug, APP_TAG, "RosMLClient::RosMLClient()");
	sAppName = "MMO Client";
}

RosMLClient::~RosMLClient()
{
	// std::cout << "RosMLClient::~RosMLClient()\n";
	ML_LOG_TAG(Debug, APP_TAG, "RosMLClient::~RosMLClient()");
	// delete[] vertices;
}


bool RosMLClient::OnUserCreate()
{
	std::cout << "RosMLClient::OnUserCreate()\n";
	return true;
}

bool RosMLClient::OnUserUpdate(float fElapsedTime)
{
	// std::cout << "RosMLClient::OnUserUpdate()\n";
	ML_LOG_TAG(Debug, APP_TAG, "RosMLClient::OnUserUpdate()");
	GameEngine::OnUserUpdate(fElapsedTime);
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