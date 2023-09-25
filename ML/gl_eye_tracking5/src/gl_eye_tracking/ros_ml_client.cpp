
#include "gl_eye_tracking/ros_ml_client.h"

RosMLClient::RosMLClient() : olc::GameEngine()
{
	// std::cout << "RosMLClient::RosMLClient()\n";
	ML_LOG_TAG(Debug, APP_TAG, "RosMLClient::RosMLClient()");
	sAppName = "MMO Client";

	n_points = 307200;
	vertices_length = n_points * 6;
  vertices_size = vertices_length * sizeof(float);

	// vertices = new float[vertices_length];
	// ParseCloudFromFile("data/res/cloud/depth_data.txt", vertices, n_points);
}

RosMLClient::~RosMLClient()
{
	// std::cout << "RosMLClient::~RosMLClient()\n";
	ML_LOG_TAG(Debug, APP_TAG, "RosMLClient::~RosMLClient()");
	
}


bool RosMLClient::OnUserCreate()
{
	std::cout << "RosMLClient::OnUserCreate()\n";
	return true;
}

bool RosMLClient::OnUserUpdate(float fElapsedTime)
{
	// std::cout << "RosMLClient::OnUserUpdate()\n";
	// ML_LOG_TAG(Debug, APP_TAG, "RosMLClient::OnUserUpdate()");
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

void RosMLClient::ParseCloudFromFile(const std::string file_path, float vertices[], const int n_points)
{
  std::ifstream file_handler(file_path);
  ML_LOG_TAG(Debug, APP_TAG, "file_path: %s", file_path.c_str());

  std::string each_value_str;

  int n_values_read_from_file  = 0;
  while(file_handler >> each_value_str)
  {
    std::string each_value_clean_str = 
      each_value_str.substr(0, each_value_str.find("f", 0));

    float value_float = std::stof(each_value_clean_str);

    vertices[n_values_read_from_file] = value_float;
    n_values_read_from_file++;
  }

  file_handler.close();
  assert(n_points == (n_values_read_from_file / 6));
}