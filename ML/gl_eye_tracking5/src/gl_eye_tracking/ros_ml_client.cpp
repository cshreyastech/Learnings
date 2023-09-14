
#include "gl_eye_tracking/ros_ml_client.h"


RosMLClient::RosMLClient() : olc::GameEngine()
{
	sAppName = "MMO Client";
}

RosMLClient::~RosMLClient()
{
	std::cout << "inside ~RosMLClient()\n";
	// delete[] vertices;
}

bool RosMLClient::OnUserCreate()
{

	return false;
}

bool RosMLClient::OnUserUpdate(float fElapsedTime)
{
	// Check for incoming network messages

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

int main(void)
{
	// struct sigaction sa;
	// memset( &sa, 0, sizeof(sa) );
	// sa.sa_handler = got_signal;
	// sigfillset(&sa.sa_mask);
	// sigaction(SIGINT,&sa,NULL);

	RosMLClient ros_ml_client;
	if (ros_ml_client.Construct(800, 600))
		ros_ml_client.Start();
	return 0;
}